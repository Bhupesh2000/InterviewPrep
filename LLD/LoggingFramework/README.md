# Logging Framework — LLD Machine Coding Round

**Level:** SDE-2 · **Language:** C++17 · **Score:** 7 / 10

A retrospective of the full round: requirements, design decisions and the reasoning
behind them, every bug found, the fixes, and the follow-up discussion.

---

## 1. Problem Statement

Design and implement an embeddable logging framework (a log4j-lite).

Baseline requirements:

- Multiple severity levels, extensible
- A configurable threshold — messages below it are not emitted
- Multiple output destinations; a single log call may fan out to more than one
- Configurable message format per destination
- Library ergonomics: `logger.info("...")`
- Thread safe — concurrent log records must never interleave

Explicitly out of scope: async/background-thread logging, log rotation, config-file parsing.

---

## 2. Final Architecture

```
Client
  │  logger.debug/info/error(string)
  ▼
Logger  «singleton»
  │  • threshold check happens HERE, before Message construction
  │  • constructs Message (captures timestamp + level at call site)
  ▼
LogHandler chain  «Chain of Responsibility»
  Debug ──► Info ──► Error          exact-match routing on level
  │  each handler owns vector<LogAppender*>  «Observer»
  ▼
LogAppender  «Strategy for destination»
  ConsoleAppender (owns std::cout)   FileAppender (owns its ofstream)
  │  • owns a mutex guarding ITS destination only
  │  • format() called OUTSIDE the lock
  ▼
Formatter  «Strategy for representation»
  PlainTextFormatter        XMLFormatter
```

### File layout

```
LoggingFramework/
├── Logger.h                  singleton, threshold, façade API
├── Message.h                 immutable log record (msg, level, timestamp)
├── MessageLevel.h            enum class + getValue() / getString()
├── TimeUtil.h                thread-safe timestamp formatting
├── main.cpp                  demo: 2 thresholds × 3 levels × 2 appenders × 3 threads
├── logHandler/
│   ├── LogHandler.h          chain node + appender registry
│   ├── DebugLogHandler.h
│   ├── InfoLogHandler.h
│   └── ErrorLogHandler.h
├── appender/
│   ├── LogAppender.h         abstract; owns formatter* + mutex
│   ├── ConsoleAppender.h
│   └── FileAppender.h
└── formatter/
    ├── Formatter.h           abstract; format(const Message&) const
    ├── PlainTextFormatter.h
    └── XMLFormatter.h
```

### Patterns used

| Pattern | Where | Why |
|---|---|---|
| Singleton | `Logger` | One global logging entry point; configured once at startup |
| Chain of Responsibility | `LogHandler` subclasses | A place to hang **per-level behaviour**, not just per-level destinations |
| Observer | `subscribe` / `notifyAll` on `LogHandler` | One message fans out to N appenders |
| Strategy | `LogAppender`, `Formatter` | Destination and representation vary independently |

---

## 3. Design Discussion

### 3.1 Where does the threshold live?

**Decision:** a single global threshold on `Logger`, checked *before* the `Message`
object is constructed.

**Why:** the stated purpose of a threshold is to avoid paying for logs you will
discard. Constructing `Message` first (string copy + `system_clock::now()`) and
*then* filtering pays exactly the cost the threshold exists to avoid.

**Interviewer pushback:** should console and file have different thresholds?

**Answer given:** not in v1. If that requirement appears, an appender-level
threshold can be added without changing the public `Logger` API — the global
threshold stays as a cheap early-out.

### 3.2 Metadata capture — call site or formatter?

**Decision:** captured at the call site, inside the `Message` constructor.

**Why (this was the strongest answer of the round):** if the timestamp were
synthesized inside the formatter, then any delay between the log call and the
format call — lock contention today, an async queue tomorrow — would be baked
into the recorded timestamp. A log claiming 22:41:41 for an event that happened
at 22:41:36 actively misleads whoever is debugging. Timestamps must be captured
as close to the event as possible.

This is also why `Message` is immutable: all fields `const`, set once at construction.

### 3.3 Chain of Responsibility — justified or over-engineered?

This was the most contested point.

**Initial justification (rejected):** "I can add a Kafka sink for error logs only."
A Kafka sink is an **appender**. `map<Level, vector<Appender*>>` handles that with
one registration and no chain. The argument described what the map already does.

**Correct justification:** CoR gives you a place to put **per-level behaviour**,
which a map has no room for:

- `ErrorHandler` capturing a stack trace before fan-out
- `ErrorHandler` rate-limiting duplicate errors
- enriching a message with request context for one level only

That is handler logic, not appender logic, and it has no home in a map.

**Accepted cost:** exact-match routing means the client registers `ConsoleAppender`
on all three handlers to get console output for every level — three calls for what
feels like one intent. Acknowledged and accepted.

### 3.4 Chain semantics

`canHandle` is exact match. `handle()` stops at the first matching handler:

```cpp
void handle(const Message& m){
    if(canHandle(m.getLevel()))  notifyAll(m);
    else if(next)                next->handle(m);
}
```

So an ERROR reaches *only* `ErrorHandler`'s appenders. This differs from log4j,
where a message reaches every appender whose threshold it clears. The design is
internally consistent; the divergence was named rather than stumbled into.

Note there are two independent filters: `Logger::threshold` (severity gate) and
`canHandle` (routing). They do different jobs and do not overlap.

### 3.5 Locking strategy

**Decision:** one mutex per appender, owned by the appender.

**Why:** the appender owns the output resource, so it is the natural place to
synchronize. Console and file writes proceed concurrently; writes to a single
destination stay atomic.

**Accepted trade-off:** no global ordering across destinations. Fine, since no
requirement asked for it.

**The hidden precondition — and the bug it caused:** per-appender locking is only
correct if appenders touch **disjoint state**. Two independent violations appeared:

1. `std::ctime` writes to a process-wide static buffer, so *formatting* was shared
   state even though it looked local. → real data race, caught by TSan.
2. The `FileAppender` stub wrote to `std::cout`, the resource `ConsoleAppender`
   guards with a *different* mutex. Two locks over one resource protect nothing.

Both are the same lesson: **verify disjointness before assuming per-resource locks
are sufficient.**

Refinement made during the fix pass: `format()` now runs **outside** the lock.
Formatting is pure once `ctime` is gone, so the mutex only needs to cover the write.

### 3.6 Ownership

**Decision:** the logger owns the handler chain; the **client** owns appenders and
formatters. The logger holds non-owning raw pointers.

**Rationale:** appenders represent application resources — stdout, files, remote
sinks. The application creates them and controls their lifetime. Raw pointer as a
deliberate "non-owning" signal is idiomatic modern C++.

**The hazard:** `Logger` is a function-local static, destroyed during static
destruction — *after* `main()`'s locals. So `delete console;` at the end of `main()`
leaves the still-alive singleton holding a dangling pointer.

**Resolution:** an explicit `Logger::shutdown()` that clears all registered
appenders, called before the client destroys them. Documented in both `Logger.h`
and `main.cpp`. (The alternative — `shared_ptr` held by the logger — was offered
and consciously declined.)

Chain ownership is manual but complete: `~Logger()` deletes the head, and
`~LogHandler()` cascades via `delete next`.

### 3.7 Configuration-time vs. logging-time state

`observers` is written only by `subscribe()` / `clearAppenders()` and read by
`notifyAll()`. Rather than lock it, the contract is that registration happens on
one thread before workers start, and clearing happens after they join.

The original code locked `subscribe()` but *not* `notifyAll()` — a lock only one
side takes is not a lock. It cost a lock per registration and guaranteed nothing.
The mutex was removed and the single-threaded-configuration contract documented.

`threshold` is different: it is genuinely written while threads run, so it is
`std::atomic<int>`.

---

## 4. Mistakes Made

Ordered by severity. Items 4 and 5 are the ones that cost the most.

### 4.1 Data race in timestamp formatting (critical)

```
WARNING: ThreadSanitizer: data race
  #0 ctime
  #1 PlainTextFormatter::format
  #2 ConsoleAppender::appendMessage
```

`std::ctime` returns a pointer into a single static buffer shared by the whole
process. Every thread formatting a record wrote to it. The console mutex did not
help because `FileAppender` called `ctime` under a *different* mutex.

Thread safety was asserted in the design discussion and never tested.

**Fix:** `TimeUtil.h` using `localtime_r` into a caller-owned `std::tm`, plus
`std::put_time`. Fixed the class of bug in one place rather than patching two
formatters.

### 4.2 Two appenders, one resource

The `FileAppender` stub wrote to `std::cout` under its own mutex — the exact
destination `ConsoleAppender` guards. Records interleaved mid-line.

**Fix:** `FileAppender` writes to a real `std::ofstream` it owns, with an open check.

### 4.3 Malformed output — never read

```
[Debug] : Thread 1 : connecting to the databaseWriting to console :Sun Aug  9...
```

`ctime` embeds `\n` *after* the timestamp and appends none at the end, so records
ran together. Separately, the XML closing tag was `<message>` instead of `</message>`
— every record was invalid XML.

Running the program and reading three lines of output would have caught both.

**Fix:** one record, one line, exactly one trailing `\n`. Correct closing tags.

### 4.4 Ignored explicit interviewer feedback (biggest single deduction)

Two corrections were given *before* coding and did not appear in the first submission:

- `const Message&` on the hot path. Everything was still by value —
  `handle`, `notifyAll`, `appendMessage`, `format`, plus `getMessageString()`
  returning by value. Roughly five string copies per log call, in a framework
  whose whole selling point is low overhead.
- The static-destruction lifetime problem, described concretely with the exact
  failure scenario. `main()` still did `delete console;` with no `shutdown()`,
  no comment, nothing.

In a real round the first submission is most of the score. Feedback given before
you write is the cheapest possible signal to act on.

### 4.5 Handler chain leaked

`~LogHandler()` did `delete next` to cascade, but `Logger` had no destructor, so
the head was never deleted and the cascade never fired. The mechanism was built;
the trigger was missing.

**Fix:** `~Logger(){ delete handler; }`. LSan now reports zero leaks.

### 4.6 Smaller items

| Issue | Fix |
|---|---|
| `setThreshold(int)` defeated the `enum class` | `setThreshold(MessageLevel)` |
| `threshold` non-atomic, read by N threads | `std::atomic<int>` |
| `notifyAll` public | moved to `protected` |
| `canHandle` / `format` non-const | marked `const` |
| single-arg constructors implicit | marked `explicit` |
| `LogHandler` rule-of-three (dtor deletes `next`, copy ops implicit → double-delete) | delete copy ctor + copy assignment |
| `getNext()` non-const | could be `const` |
| `debug`/`info`/`error` are three copies of the same body | private `log(level, msg)` + thin wrappers |

### 4.7 Unforced errors in the discussion

- The CoR justification took two attempts; the first argument actually made the
  case for the alternative design. Know why you picked a pattern before being asked.
- The UML omitted the mutex, which had already been discussed.

### 4.8 Fixes that went beyond what was asked

Worth recording, because they were the strongest part of the round:

- `TimeUtil.h` as a shared utility rather than two local patches
- `format()` moved outside the lock — correct, and the point of per-appender locking
- **XML escaping** for `& < > " '` — a correctness bug the interviewer had missed
- Comments that explain *why* a fix was made, not what the code does

---

## 5. Follow-Up Questions

### Q1 — `addAppender` fails silently

`addAppender` walks the chain and returns quietly when no handler matches. Add
`WARN` to the enum, forget the handler, and every WARN log vanishes with no
diagnostic anywhere.

**Answer given:** throw an error on an unhandled level.

**Assessment — half right.** The two failure sites need different policies:

- **Registration time** (`addAppender`): throw. Programmer error, happens at
  startup, fail fast and loud.
- **Log time** (`handle` falling off the end of the chain): **never throw.**
  A logging framework must not be able to kill its host — logging is diagnostic
  infrastructure and cannot become the outage. Use a last-resort fallback:
  write to `stderr` or an internal error stream. log4j has exactly this.

### Q2 — Ordering baked into enum values

`DEBUG=1, INFO=2, ERROR=3` with `threshold <= level`. Add `FATAL`; then add
`TRACE` *below* `DEBUG`.

**Answer given:** those levels won't be routed to any appender.

**Assessment — symptom, not cause.** The missing handler is real but shallow. The
actual hazard: TRACE must sort below DEBUG, and DEBUG is already `1`. You either
use `0` or renumber the enum. **Renumbering is the killer** — those integers are
visible to clients. Anyone who persisted `threshold=2` in a config file or sent the
value over the wire silently gets a different level after the change.

**Lesson:** enum values are a serialization/ABI surface, not an implementation
detail. Two mitigations:

1. Leave gaps: `TRACE=10, DEBUG=20, INFO=30, WARN=40, ERROR=50, FATAL=60` — insert
   without renumbering.
2. Keep the ordinal away from clients behind a `severity(MessageLevel)` function,
   so comparison logic is the only thing that depends on the numbers.

### Q3 — Extending to async (discussed, not implemented)

Deliberately out of scope, but the design already accommodates it: because metadata
is captured at the call site, moving fan-out onto a background thread does not
corrupt timestamps. The producer would enqueue the `Message`; a consumer thread
would drain the queue into the handler chain. Open questions: bounded vs. unbounded
queue, drop policy under backpressure, and flushing on shutdown.

---

## 6. Verification

```bash
g++ -std=c++17 -pthread -Wall -Wextra -o main main.cpp && ./main
g++ -std=c++17 -pthread -fsanitize=thread  -g -o main_tsan main.cpp && ./main_tsan
g++ -std=c++17 -pthread -fsanitize=address -g -o main_asan main.cpp && ./main_asan
```

| Check | Before | After |
|---|---|---|
| `-Wall -Wextra` | clean | clean |
| ThreadSanitizer | 1 data race (`ctime`) | **0** |
| LeakSanitizer | handler chain leaked | **0** |
| Output well-formed | no — records ran together, invalid XML | **yes** |

Console:

```
----- threshold = DEBUG -----
Writing to console : 2026-08-09 22:41:36 [Debug] : Thread 2 : connecting to the database
Writing to console : 2026-08-09 22:41:36 [Info] : Thread 2 : request handled
Writing to console : 2026-08-09 22:41:36 [Error] : Thread 2 : failed to write to disk
...
----- threshold = ERROR -----
Writing to console : 2026-08-09 22:41:36 [Error] : Thread 4 : failed to write to disk
```

`app.log`:

```xml
<record><timestamp>2026-08-09 22:41:36</timestamp><level>Error</level><message>Thread 2 : failed to write to disk</message></record>
```

---

## 7. Assessment

### Score: 7 / 10

**Positives**

- Requirements framing was strong — appender/formatter separation arrived unprompted.
- The metadata-capture answer (async timestamp skew) was the best reasoning of the
  round: a real mechanism, not a memorised rule.
- Design choices were defended rather than asserted, including correct pushback on
  the ownership model.
- The revision pass was excellent: fixed classes of bugs rather than instances,
  added XML escaping unprompted, moved formatting out of the critical section, and
  commented the *why*.
- Final code is clean under TSan, LSan, and `-Wall -Wextra`.

**Negatives**

- **The first submission ignored two explicit corrections** given before coding
  started. This is the single largest gap between 7 and 8.5.
- **Output was never read.** Two visible defects survived to submission.
- **Thread safety was claimed but not tested.** The race was in the exact subsystem
  under careful discussion. Claiming a concurrency property obliges you to
  demonstrate it.
- The CoR justification needed two attempts; the first argued for the alternative.
- Follow-ups landed on symptoms rather than root causes.

### What to do differently next time

1. Run it and **read the output** before saying "done" — 30 seconds, two bugs.
2. Keep a written checklist of interviewer corrections; walk it before submitting.
3. If you claim thread safety, run TSan. If you claim no leaks, run LSan.
4. Before naming a pattern, have the one-sentence justification ready — and check
   that the justification doesn't secretly argue for the simpler alternative.
5. On follow-ups, ask "what is the *mechanism* that breaks?" rather than "what does
   the user see?"

---

## 8. Known Limitations

- Configuration is startup-only; `subscribe` / `clearAppenders` are not thread safe
  by contract.
- Exact-match routing means one appender must be registered once per level.
- `addAppender` still fails silently on an unmatched level (Q1 fix not implemented).
- Enum values still encode ordering directly with no gaps (Q2 fix not implemented).
- No async logging, no log rotation, no config-file parsing — all out of scope.
- `localtime_r` is POSIX; Windows needs `localtime_s`.
