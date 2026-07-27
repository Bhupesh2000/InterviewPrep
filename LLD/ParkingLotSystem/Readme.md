# Parking Lot — LLD / Machine Coding Review

**Level:** SDE-2 · **Language:** C++17 · **Round:** Low Level Design + Machine Coding
**Verdict:** 6 / 10 — solid structural instincts, but the non-functional requirement you claimed (concurrency) is not actually met, and it was the one thing flagged for you twice before you wrote code.

---

## 1. Problem Statement

Design a parking lot system. Multiple floors, each with parking spots. Vehicles arrive at an entry gate, receive a ticket with an assigned spot, and pay at an exit gate based on duration parked.

### Scope you set

**In scope**

- Single entry gate, single exit gate
- Two vehicle types: `TWO_WHEELER`, `FOUR_WHEELER`
- Strict type matching — a 2-wheeler parks only in a 2-wheeler spot
- Multiple floors, each floor holding spots
- Fixed-rate pricing, pluggable for future strategies
- Random spot allocation, pluggable for future strategies

**Explicitly deferred**

- Multiple gates
- Reservations / pre-booking
- Persistence
- Duration-based, slab-based, or dynamic pricing

**Non-functional goals you stated**

- Extensible
- Scalable
- Safe under concurrent calls ← **this is where the submission falls down**

---

## 2. Design Discussion — Decisions Made Before Coding

### 2.1 Ticket ordering: before or after spot allocation

Your initial flow issued the ticket first, then hunted for a spot. You defended it on two grounds.

**Argument 1 — analytics.** "A ticket per attempt lets me track how often we fail to find a spot."

This is a legitimate requirement, but it points at a different entity. A `Ticket` in this domain means *"you have a spot, present this at exit to pay."* Overloading it to also mean *"you asked and got nothing"* forces a nullable `spot` field and an `INVALIDATED` state that every downstream consumer must defensively check. The right shape is a separate `ParkingRequest` record, or simply an event/log emitted on the failure path.

**Argument 2 — race conditions.** "Creating the ticket after allocation means I must reserve, create, then mark assigned — that's racy."

This one does not hold, and it is worth internalising why:

```cpp
// Order A (your original)              // Order B (chosen)
ticket = new Ticket();                  spot = claimFreeSpot();   // <-- atomic
spot   = claimFreeSpot();               if (!spot) return nullptr;
if (!spot) ticket.invalidate();         ticket = new Ticket(spot);
ticket.assign(spot);
```

The contention lives entirely inside `claimFreeSpot` — find-free-spot and mark-it-taken must be atomic, or two vehicles get the same spot. Constructing a `Ticket` is a thread-local heap allocation that contends with nothing. Moving it earlier neither shrinks nor protects the critical section; it only leaves you holding mutable state that needs unwinding on the failure path.

**Resolution:** allocate spot first, then construct the Ticket. The Ticket becomes valid-by-construction, which removes a whole class of downstream null checks.

### 2.2 Strategy placement

Two independent axes were correctly separated:

| Axis | Interface | Lives on | Why there |
|---|---|---|---|
| Which spot to pick | `IParkingLookupStrategy` | `ParkingSpotManager` | Operates on exactly the list it needs — already filtered by type and level |
| How much to charge | `IPricingStrategy` | `CostComputation` | Depends only on the ticket |
| How payment is taken | `IPaymentStrategy` | Passed in at `exit()` | Chosen per transaction, not per lot |

Keeping *how much* separate from *how paid* is correct and is something many candidates fuse into one class.

### 2.3 Manager subclassing — corrected pre-code

Your UML had `TwoWheelerManager` and `FourWheelerManager` as subclasses of `ParkingSpotManager`. They differed only by the *name* of the vector they held.

That is inheritance used to model data. It also directly contradicts the extensibility you claimed: adding trucks would require a new class, a new registration, and changes to level construction. Since `ParkingLevel` already keys managers by `VehicleType`, the subclass stored that information a second time.

**Resolution:** one concrete `ParkingSpotManager`. You applied this. Adding a vehicle type is now a config change, not a code change.

### 2.4 Lock granularity — discussed, then not applied

The conversation landed on: **one mutex per `ParkingSpotManager`**, with the critical section covering find-and-occupy as a single unit.

Rationale: a single lot-wide mutex is correct but serialises everything — a bike parking on floor 1 blocks a car parking on floor 5. A per-manager mutex confines contention to vehicles competing for the same type on the same level, which is the real contention.

You even wrote the shape yourself:

```cpp
ParkingSpot* tryPark(VehicleType type) {
    std::lock_guard<std::mutex> lock(mtx);   // per-manager
    for (ParkingSpot* s : spots) {
        if (s->isFree()) { s->occupy(); return s; }   // check + occupy, no gap
    }
    return nullptr;
}
```

**This is not what shipped.** See §4.1.

### 2.5 TOCTOU on `hasAvailability()`

Flagged before coding:

```cpp
if (level->hasAvailability(type))   // thread A: true
    spot = level->park(type);       // thread B took the last spot → nullptr
```

You were asked to either delete these methods or demote them to pure diagnostics that nothing branches on. You did neither — `ParkingBuilding::park` branches on `hasAvailability` today.

### 2.6 Unpark addressing

`ParkingBuilding::unpark(ParkingSpot*)` with a bare spot pointer has no way to find the owning level and manager without scanning everything. Resolution: the `Ticket` records the floor id. You added `floorId`. You did **not** add `VehicleType` — which is why the unpark path ended up unusable. See §4.3.

---

## 3. Final Architecture

```
ParkingLot
 ├── ParkingBuilding
 │    └── unordered_map<int, ParkingLevel*>
 │         └── unordered_map<VehicleType, ParkingSpotManager*>
 │              ├── vector<ParkingSpot*>
 │              └── IParkingLookupStrategy*  →  RandomLookupStrategy
 ├── EntryGate  (ParkingBuilding*)
 │     Ticket* allocateSlot(Vehicle*)
 └── ExitGate   (ParkingBuilding*, CostComputation*)
       void exit(Ticket*, IPaymentStrategy*)

CostComputation ── IPricingStrategy  → FixedPricingStrategy
IPaymentStrategy → UPIPayment, CashPayment

Ticket { id, vehiclePlateNo, timeOfEntry, timeOfExit, floorId, ParkingSpot*, isActive }
ParkingSpot { id, isFree, VehicleType }
```

Directory layout is clean and consistent: `enum/`, `model/`, `manager/`, `parkingLookupStrategy/`, `pricing/`, `payment/`. Header guards everywhere. Compiles with `-Wall -Wextra` with a single unused-parameter warning.

---

## 4. Findings

### CRITICAL

#### 4.1 — `ParkingSpotManager::park()` has no lock at all

```cpp
ParkingSpot* park(){
    ParkingSpot* spot = parkingStrategy -> findSpot(parkingSpots);
    spot -> allocate();          // unguarded, and unconditional
    return spot;
}
```

Two failures in three lines:

1. **No mutex.** This is the exact method the interview identified as the critical section. There is no `std::mutex` member on `ParkingSpotManager`.
2. **Null dereference.** `findSpot` returns `nullptr` when nothing is free, and it is dereferenced without a check. The demo does not crash only because `ParkingBuilding::park` guards the call with `hasAvailability` — which, per §2.5, is precisely the check that is not reliable under concurrency. One TOCTOU miss and this is a segfault.

**Fix:**

```cpp
class ParkingSpotManager {
    std::vector<ParkingSpot*> parkingSpots;
    IParkingLookupStrategy*   parkingStrategy;
    VehicleType               type;
    mutable std::mutex        mtx;
public:
    ParkingSpot* park(){
        std::lock_guard<std::mutex> lock(mtx);
        ParkingSpot* spot = parkingStrategy->findSpot(parkingSpots);
        if (!spot) return nullptr;
        spot->allocate();
        return spot;
    }
    void unpark(ParkingSpot* spot){
        std::lock_guard<std::mutex> lock(mtx);
        spot->release();
    }
};
```

#### 4.2 — Entry and exit synchronise on different mutexes → confirmed data race

The lock migrated up to `ParkingBuilding::park`, inside the loop:

```cpp
for(auto it : levels){
    std::lock_guard<std::mutex> lock(mtx);   // building-wide
    if(level -> hasAvailability(type)){ spot = level -> park(type); ... }
}
```

Meanwhile `ExitGate::exit` takes **its own** mutex and mutates the spot directly:

```cpp
std::lock_guard<std::mutex> lock(mtx);       // ExitGate's mutex — a different lock
spot -> release();
```

Two different mutexes guarding the same `ParkingSpot::isFree` byte is not mutual exclusion. ThreadSanitizer confirms it, and the report even names the two distinct locks (`M12` vs `M13`):

```
WARNING: ThreadSanitizer: data race
  Read of size 1 by thread T2 (mutexes: write M12):
    ParkingSpot::isSpotFree()      ParkingSpot.h:23
    ParkingSpotManager::hasFreeSpot()
    ParkingLevel::hasAvailability()
    ParkingBuilding::park()        ParkingBuilding.h:32
    EntryGate::allocateSlot()

  Previous write of size 1 by thread T1 (mutexes: write M13):
    ParkingSpot::release()         ParkingSpot.h:31
    ExitGate::exit()               ExitGate.h:32
```

There is a second cost. Because the lock is building-wide, every allocation across every floor and every vehicle type is serialised — the exact behaviour §2.4 set out to avoid. So the design pays the full price of a global lock and still does not get correctness.

#### 4.3 — The entire unpark path is dead code

```
$ grep -rn "unpark" --include=*.h .
manager/ParkingSpotManager.h:37:    void unpark(ParkingSpot* spot){
model/ParkingBuilding.h:41:         void unpark(int levelId, VehicleType type, ParkingSpot* spot){
model/ParkingBuilding.h:43:             levels[levelId] -> unpark(type, spot);
model/ParkingLevel.h:40:            void unpark(VehicleType type, ParkingSpot* spot){
model/ParkingLevel.h:41:                parkingSpotManagersMap[type] -> unpark(spot);
```

No call site anywhere. `ExitGate` reaches through the object graph and calls `spot->release()` directly, bypassing building, level, and manager.

The root cause is instructive: `ParkingBuilding::unpark` requires `(levelId, VehicleType, spot)`, but `Ticket` stores `floorId` and `ParkingSpot*` and **no `VehicleType`**. The exit gate literally could not call it. Rather than fixing the Ticket, the layer was bypassed — and with it, the lock that layer was supposed to own. §4.2 is the direct consequence.

Note that `spot->getVehicleType()` was available the whole time; the parameter is arguably redundant, since the manager that owns a spot already implies its type.

#### 4.4 — Non-atomic ticket ID generation

```cpp
inline static int nextId = 1;
Ticket(...) : id(nextId ++), ...
```

`nextId++` is read-modify-write, not atomic. Measured over 8 threads × 100 vehicles:

```
TEST A  tickets issued=800  unique ids=794  *** DUPLICATE TICKET IDs ***
```

Six collisions. In a real lot that is six vehicles that cannot be told apart at the exit gate. Fix: `inline static std::atomic<int> nextId{1};` — or better, move ID generation out of the entity into a `TicketFactory` / id-generator that can later be swapped for a UUID or a DB sequence.

### MAJOR

#### 4.5 — Spot released before payment is taken

```cpp
ticket -> setTimeOfExit(timeOfExit);
ParkingSpot* spot = ticket -> getParkingSpot();
spot -> release();                                  // <-- freed first
int amountToPay = costComputation -> calculateParkingFair(ticket);
paymentStrategy -> pay(amountToPay);                // <-- charged after
ticket -> deactivateTicket();
```

If `pay()` throws or fails, the spot is already free and the ticket is still active — inventory and billing are now inconsistent. Correct order: compute → pay → release → deactivate. `IPaymentStrategy::pay` returning `void` compounds this; there is no way to signal failure. It should return a status or a `Payment` record.

#### 4.6 — Time modelled as `std::string`, which makes the pricing strategy inert

```cpp
std::string timeOfEntry = "01:01:2026 01:01:01";   // hard-coded literal in EntryGate
std::string timeOfExit  = "01:01:2026 11:01:01";   // hard-coded literal in ExitGate
```

```cpp
int calculatePrice(Ticket* ticket) override { return 100; }   // ticket unused
```

This is the most consequential design miss after the concurrency issues. The whole justification for `IPricingStrategy` was *"fixed rate now, hourly/slab/dynamic later."* But no duration-based strategy can be written against a `std::string` timestamp without parsing text, and the entry/exit times are compile-time constants regardless. The extension point exists in the type system and is unusable in practice.

`FixedPricingStrategy` returning a bare `100` with the parameter unused — the sole compiler warning — is the symptom.

**Fix:** `std::chrono::system_clock::time_point` for both timestamps, injected via a `Clock` abstraction so tests can control it:

```cpp
struct IClock { virtual std::chrono::system_clock::time_point now() const = 0; };

int calculatePrice(Ticket* t) override {
    auto hours = std::chrono::duration_cast<std::chrono::hours>(
                     t->getTimeOfExit() - t->getTimeOfEntry()).count();
    return ratePerHour * std::max<long>(1, hours);
}
```

#### 4.7 — TOCTOU check retained, plus a redundant scan

`ParkingBuilding::park` calls `hasAvailability(type)` (O(n) scan) and then `park(type)` (another O(n) scan for the same thing). Twice the work, and the gap between them is the race §2.5 warned about. `park()` returning `nullptr` is the only trustworthy answer; `hasAvailability` should be deleted from the allocation path and kept, if at all, for reporting only.

#### 4.8 — `ParkingSpot::allocate()` / `release()` are public and unsynchronised

These are the two mutating operations in the system and anyone holding a `ParkingSpot*` can call them without holding any lock. That is precisely what `ExitGate` did in §4.3. Make them private with `ParkingSpotManager` as a `friend`, or move the ownership of mutation entirely into the manager.

### MINOR

| # | Issue | Detail |
|---|---|---|
| 4.9 | `RandomLookupStrategy` is not random | It is a first-fit linear scan. Either rename it `FirstFitLookupStrategy` or implement actual random selection. Naming that lies about behaviour is a real review comment. |
| 4.10 | `ParkingLevel::mtx` is decorative | Acquired only in `addParkingSpotManager`. `park`, `unpark`, and `hasAvailability` — the methods that matter — take nothing. |
| 4.11 | `isActive` not renamed | Agreed in discussion to rename to reflect *"still parked"*. A `TicketStatus` enum (`ACTIVE`, `PAID`, `LOST`) leaves room to grow. |
| 4.12 | `ExitGate` mutex is at the wrong level | A single gate-wide mutex serialises every exit in the building. Should sit on the manager alongside the park lock. |
| 4.13 | `ParkingSpotManager` has no `VehicleType` member | Requested during UML review. Without it the manager cannot validate that an incoming request matches its spots. |
| 4.14 | Raw `new`/`delete` throughout | For SDE-2, `std::unique_ptr` for ownership and raw pointers only for non-owning references. Ownership is currently spread across five destructors and has to be reasoned about manually. |
| 4.15 | `ExitGate` double-exit check outside the lock | `if(ticket->isActiveTicket())` is evaluated before `lock_guard`. The window is small enough that 500 rounds of two racing threads did not reproduce a double charge, but it is a real TOCTOU. Move the check inside the lock. |
| 4.16 | `Ticket` lacks a `VehicleType` | Root cause of 4.3. |

---

## 5. Verification Performed

| Check | Result |
|---|---|
| `g++ -std=c++17 -Wall -Wextra -pthread` | Compiles; 1 warning (unused `ticket` in `FixedPricingStrategy`) |
| Single-threaded demo (`main.cpp`) | Correct. Turn-away, re-park after exit, and double-exit no-op all behave |
| 8 threads × 100 parks — ticket id uniqueness | **FAIL** — 794 unique out of 800 |
| 4 threads, concurrent park + exit, ThreadSanitizer | **FAIL** — 2 distinct data races (`ParkingSpot::isFree`, `Ticket::nextId`) |
| 500 rounds, two threads exiting the same ticket | Pass, but by luck — the TOCTOU in 4.15 is real |

The `main.cpp` demo deserves credit on its own: it covers the happy path, the full-lot turn-away, re-parking into a freed spot, and re-exiting a closed ticket. That is better exercise coverage than most machine-coding submissions bring.

---

## 6. Follow-Up Questions

Questions that would have come next in the round, with what a strong answer looks like.

**Q1. Two threads, last four-wheeler spot on level 3. Walk through it line by line and tell me who wins.**
Right now: both enter `ParkingBuilding::park`, both serialise on the building mutex, so one wins — but only because the lock is far coarser than intended. With the intended per-manager lock: both reach `ParkingSpotManager::park`, one acquires, finds and occupies, releases; the second finds nothing and returns `nullptr`, which propagates up as a turned-away vehicle.

**Q2. Push the mutex down to `ParkingSpot` instead of the manager. What breaks?**
Find-free-then-occupy is no longer atomic. Two threads both observe spot 5 free, both lock spot 5 in turn, and the second overwrites the first's allocation. Per-spot locks only work with a CAS on the free flag (`compare_exchange_strong` on an `std::atomic<bool>`), turning the scan into a lock-free claim attempt. That is a legitimate alternative design — and strictly better under high contention — but it must be a CAS, not a mutex.

**Q3. Ten entry gates instead of one. What changes?**
Nothing in the domain model, which is the point of a good design. `EntryGate` is stateless apart from its `ParkingBuilding*`, so N gates share one building. What changes is contention: N gates hammering one lock. That is when per-manager locking stops being a nicety and starts being necessary, and when the level-selection policy starts to matter — ten gates all first-fitting into level 1 will hot-spot one mutex.

**Q4. Someone loses their ticket. Model it.**
Needs a lookup by plate number — an index the system does not currently have. Add `unordered_map<string, Ticket*> activeTickets` on a `TicketRepository`, plus a `LOST` status and a lost-ticket pricing rule (typically flat penalty, since entry time is unverifiable). This is a good probe for whether the candidate reaches for a repository or starts scanning every spot.

**Q5. Pricing changes to: free for the first 15 minutes, then ₹30/hour, capped at ₹300/day. Where do you touch?**
Should be a single new `IPricingStrategy` implementation and one line at construction. In the current code it also requires converting `Ticket`'s timestamps from `std::string` to `chrono` — which is the practical proof that 4.6 matters. An extension point you cannot extend without editing the core entity is not an extension point.

**Q6. `hasAvailability()` returns true and then `park()` returns null. Is that a bug?**
No — that is correct behaviour for a concurrent system and the caller must handle it. The bug is *branching* on `hasAvailability` as though it were a guarantee, which is what `ParkingBuilding::park` does today, and what makes the unchecked `spot->allocate()` in 4.1 a latent crash.

**Q7. How would you unit-test the allocation logic?**
Inject a deterministic `IParkingLookupStrategy` stub so spot selection is predictable, and an `IClock` stub so pricing is testable. Neither seam exists today for time. Worth noting that the lookup strategy interface *does* already give you the first seam for free — that part of the design pays off.

---

## 7. Assessment

### Positives

- **Correct layering.** Building → Level → SpotManager → Spot is the right decomposition, and the lookup strategy sits at the level where it has exactly the data it needs. Many candidates put spot selection on the building and end up passing the whole object graph around.
- **Genuinely separated concerns in pricing.** `IPricingStrategy` (how much) and `IPaymentStrategy` (how paid) as independent axes is a real design insight, not a memorised pattern.
- **Took feedback and applied it.** The manager subclasses were removed, `floorId` was added to `Ticket`, gate/building wiring was made consistent. No defensiveness once an argument was shown to be wrong.
- **Defended decisions with reasons.** The ticket-ordering argument was wrong on the concurrency half but the analytics half was a legitimate requirement worth naming. Reasoned pushback is more useful than compliance.
- **Clean, consistent code.** Directory structure, header guards, `const` correctness on getters, destructors present, working demo. It compiles clean at `-Wall -Wextra`. This is above average for machine coding.
- **The demo `main.cpp` is well constructed.** Turn-away, re-park, double-exit — deliberately chosen edge cases, not just a happy path.

### Negatives

- **The stated non-functional requirement is not met.** Concurrency was claimed, discussed twice, and the exact lock placement was agreed — and then the lock landed somewhere else, guarding a different object, while the method that needed it got nothing. The gap between "I'll use a mutex" and a correctly placed mutex is where this submission loses most of its marks.
- **A layer was bypassed rather than fixed.** `ExitGate` calling `spot->release()` directly is the single most damaging line in the codebase. It orphaned three `unpark` methods, broke the locking discipline, and created the confirmed data race. The trigger was a missing `VehicleType` on `Ticket` — a two-minute fix that instead became an architectural hole.
- **Extension points that cannot be extended.** `IPricingStrategy` is unusable for any duration-based rule because time is a hard-coded `std::string`. The pattern is present; the capability is not. Worth remembering that a strategy interface is only as good as the data it receives.
- **Warned-about issues shipped anyway.** The `hasAvailability` TOCTOU was raised before coding and is still on the allocation path. `isActive` was agreed to be renamed and was not. Closing the loop on review comments matters.
- **No null check on the hottest path.** `spot->allocate()` with no guard, where `findSpot` explicitly returns `nullptr`, in the one method under discussion the entire round.

### Rating: **6 / 10**

Design judgement sits around 7–8. The decomposition is sound, the strategy placement is thoughtful, and the response to feedback is exactly what you want from someone you will be reviewing code with. That part reads as SDE-2.

Execution on the concurrency requirement sits around 4, and it is weighted heavily because you named it yourself as a goal, it was discussed twice in detail, and the correct approach was agreed before a line was written. Shipping a build where entry and exit take different mutexes over the same byte is the kind of defect that surfaces in production at 2am, not in code review.

**Recommendation:** borderline. Not a no — the structural thinking is real and the collaboration is good. But I would want a second round focused purely on concurrent code before making a call.

### What to work on

1. **After writing any locked code, ask "which object owns this byte, and does every writer hold the same lock?"** Both critical findings collapse into that one question.
2. **Run ThreadSanitizer on anything with `std::thread` in it.** `g++ -fsanitize=thread` found both races in seconds. Build it into your practice loop so it becomes a reflex before submission.
3. **Grep for uncalled methods before you submit.** Three orphaned `unpark` implementations are a signal that a design decision got quietly abandoned mid-flight.
4. **Model time as `chrono`, never as a string.** It is a small habit that here silently disabled the main extension point of the design.
5. **Keep a written checklist of interviewer comments and tick them off before you hand over.** Two agreed changes did not make it into the code — that is cheap to fix and it reads badly when it happens.

---

## 8. Reference Fix for the Critical Path

```cpp
// manager/ParkingSpotManager.h
class ParkingSpotManager {
    VehicleType               type;
    std::vector<ParkingSpot*> parkingSpots;
    IParkingLookupStrategy*   parkingStrategy;
    mutable std::mutex        mtx;

public:
    ParkingSpotManager(VehicleType type, IParkingLookupStrategy* s)
        : type(type), parkingStrategy(s) {}

    VehicleType getVehicleType() const { return type; }

    // Sole writer of ParkingSpot::isFree on the allocation path.
    ParkingSpot* park(){
        std::lock_guard<std::mutex> lock(mtx);
        ParkingSpot* spot = parkingStrategy->findSpot(parkingSpots);
        if (!spot) return nullptr;          // full: the single trustworthy answer
        spot->allocate();
        return spot;
    }

    // Sole writer on the release path — same mutex, which is the whole point.
    void unpark(ParkingSpot* spot){
        std::lock_guard<std::mutex> lock(mtx);
        spot->release();
    }
};
```

```cpp
// model/ParkingBuilding.h — no building-wide lock on the hot path
std::pair<int, ParkingSpot*> park(VehicleType type){
    for(auto& [levelId, level] : levels){        // levels immutable after setup
        if(ParkingSpot* spot = level->park(type))  // atomic; null means full
            return {levelId, spot};
    }
    return {-1, nullptr};
}
```

```cpp
// model/ExitGate.h — route through the layer, and pay before releasing
void exit(Ticket* ticket, IPaymentStrategy* paymentStrategy){
    if(!ticket->tryClose()) return;              // atomic compare-and-close

    ticket->setTimeOfExit(clock->now());
    int amount = costComputation->calculateParkingFair(ticket);
    if(!paymentStrategy->pay(amount)){           // pay() must report failure
        ticket->reopen();
        return;
    }
    building->unpark(ticket->getFloorId(),
                     ticket->getParkingSpot()->getVehicleType(),
                     ticket->getParkingSpot());  // release last, via the owner
}
```

Three changes: the lock lives with the data it protects, every writer goes through that lock, and money moves before inventory does.