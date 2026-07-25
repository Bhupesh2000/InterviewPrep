# Rate Limiter — LLD / Machine Coding

**SDE-2 · C++17 · Low Level Design + Machine Coding round**

In-process, thread-safe rate limiting library. A service calls
`allowRequest(user)` before doing work; the limiter answers whether the request
is within that user's quota.

---

## Requirements

- Per-user quota tracking
- Multiple algorithms — Fixed Window and Token Bucket, extensible to Sliding Window
- Per-tier configuration (free: 10 req/min, premium: 1000 req/min)
- Multi-threaded, single process

**Out of scope (deliberate):** key resolution service, user service/persistence,
eviction, distributed operation, and a richer return type than `bool`.

---

## Design

| Pattern | Where | Why |
|---|---|---|
| Strategy | `RateLimiter` base + two concrete limiters | New algorithm = new class, no edits to existing ones |
| Factory | `RateLimiterFactory` | Service never names a concrete limiter type |

**Key decisions**

- **Tier and algorithm are decoupled.** The mapping is a runtime argument to
  `addNewRateLimiter(tier, algo, config)`, not a hardcoded switch. Moving the
  free tier to a token bucket is a config change.
- **One limiter per tier, holding per-user state** — rather than one limiter
  object per user, which multiplies object count and scatters the locking.
- **Single map to a per-user struct**, not parallel maps — one lookup, no chance
  of two maps disagreeing.
- **One config class for both algorithms.** Token Bucket derives capacity and
  refill rate from `maxRequests` / `windowInSeconds`.

## Structure

```
enum/UserTier.h             FREE, PREMIUM
model/User.h                { id, tier }
model/RateLimiterConfig.h   { maxRequests, windowInSeconds }
rateLimiter/RateLimiter.h   abstract base
    ├── FixedWindowRateLimiter.h
    └── TokenBucketRateLimiter.h
factory/RateLimiterFactory.h
service/RateLimiterService.h   facade: tier -> limiter
main.cpp                       test harness
```

`RateLimiterService` reads the user's tier, picks that tier's limiter, and
delegates. Unregistered tiers fail closed.

## Algorithms

**Fixed Window** — time split into epoch-aligned buckets; each user holds a count
and the window it belongs to. O(1) memory. Cheap, but has a boundary burst.

**Token Bucket** — per-user bucket refilled *lazily* at request time, so nothing
runs in the background. O(1) memory. Allows controlled bursts up to capacity and
has no boundary-burst flaw.

## Concurrency

One `std::mutex` per limiter, held across the whole of `allowRequest` — the
critical section covers find-or-create plus the read-modify-write, so two threads
can't both see "quota available" and both consume it.

Verified clean under ThreadSanitizer (8 threads × 50 requests, quota 100 →
exactly 100 allowed).

**Tradeoff:** all users of a tier serialise on one lock. Lock striping
(`hash(userId) % N`) is the natural next step; see Future Extensions for what it
costs. Service registration is assumed startup-only and is not itself guarded.

## Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -pthread main.cpp -o rate_limiter && ./rate_limiter
```

Sanitizers: add `-fsanitize=address,undefined` or `-fsanitize=thread`.
Exit code `0` if all checks pass.

## Tests

35 assertions across 8 scenarios: quota enforcement, window reset, per-user
isolation, burst-then-refill, refill capped at capacity, tier independence with a
colliding user id, unregistered tier, unknown algorithm, and concurrency.

Fixed-window tests park at a window boundary first so counts are deterministic
rather than flaky.

---

## Known Limitations (as submitted)

1. **Token Bucket under-delivers.** Refill truncates to whole seconds and resets
   `lastRefillTime` to `now`, discarding the unconsumed remainder. Measured at
   ~56% of the configured rate under sustained polling. *Correctness bug.*
2. **Memory leaks** (ASan-confirmed). Unknown algorithm drops the config;
   re-registering a tier overwrites raw pointers without deleting.
3. **Split ownership** — the service owns configs in a second map while limiters
   hold raw borrowed pointers. Root cause of #2.
4. **Fixed Window boundary burst** — up to 2× the configured rate across a bucket
   edge. Algorithmic, not an implementation defect. Token Bucket is immune.
5. Minor: `system_clock` used for elapsed math (should be `steady_clock`), `new`
   in a default argument, redundant map lookups, no `const` getters,
   `main.dSYM/` committed.

## Planned Fixes

- Refill in milliseconds; advance `lastRefillTime` by the time consumed instead
  of resetting it. Switch to `steady_clock`.
- `unique_ptr` for limiters, `shared_ptr` (or by-value) for configs; drop the
  duplicate config map in favour of a `setConfig()` on `RateLimiter`. Both leak
  paths then disappear structurally.
- Cleanups: single-lookup map access, `const`-correctness, remove build artifacts.

## Future Extensions

**Sliding Window** — *Log* keeps per-user timestamps: exact, but O(maxRequests)
memory per user, fatal at scale. *Counter* weights the previous window by
overlap: O(1) memory, slightly approximate, and what production systems actually
run. Both drop in as new strategies.

**Lock striping** — N mutexes by `hash(userId) % N`. Breaks any global view: a
cross-shard total needs all N locks for a consistent snapshot, so the usual
answer is padded per-shard counters summed on read, accepting a fuzzy total.
*Sharding buys throughput by giving up global consistency.*

**Distributed** — state moves to Redis. The hard part is atomic read-modify-write
across a network; `INCR` then `EXPIRE` races, so the whole check-and-decrement
goes into a Lua script. Then two unavoidable decisions: the per-request network
hop (mitigate with local approximate limiting + periodic sync), and fail-open vs
fail-closed on store outage — limiters almost always fail open. Use the store's
clock, not per-server clocks.

**Also:** entry eviction (interacts badly with per-entry locking), and a richer
return type carrying `remaining` / `retryAfter` for `X-RateLimit-*` headers.

---

## Interview Record

**Positives** — clean layering; Strategy and Factory used for real reasons;
responsive to design feedback (merged the parallel maps, decoupled tier from
algorithm); thread safety correct first time and TSan-clean. Test suite was the
strongest part — boundary alignment avoids the flaky test most candidates ship,
and asserting an exact count in the concurrency test is above the bar.

**Negatives** — knew about the refill imprecision but never sized it; "known
simplification" doesn't hold at 56%. Memory management was the weak spot. Two
pieces of review feedback silently didn't land — if deprioritising for time, say
so. Blanked on lock contention and distributed limiting, both standard at this
level. Missed that the token bucket already solved the fixed-window boundary
problem, suggesting the algorithms were considered in isolation rather than
compared.

**Rating: 7 / 10.** Design and implementation carry the round; the depth
questions are where it falls short.

**Study list:** lock striping and false sharing · Sliding Window Log vs Counter ·
Redis-backed distributed limiting and Lua atomicity · fail-open vs fail-closed.

> The summary being fished for: *free tier's fixed window has a 2× boundary
> burst, premium's token bucket doesn't, and neither works across servers
> without moving state to Redis.*