# Elevator System — LLD / Machine Coding Round

**Level:** SDE-2 · **Language:** C++ · **Round type:** LLD + Machine Coding
**Verdict:** 5.5 / 10

---

## 1. The Problem

> Design an elevator control system for a building. Multiple elevators serve multiple floors.
> People press buttons outside on a floor (up/down) and inside the cabin (a specific floor).
> The system decides which elevator serves which request, and each elevator moves accordingly.

Deliberately vague. The candidate was expected to scope it, state assumptions, and defend design choices before writing code.

---

## 2. Requirements & Scope

### In scope

- A `Building` with N floors and M elevator cars
- **External (hall) requests:** `(floor, direction)` — pressed on a floor panel
- **Internal (car) requests:** `(destinationFloor)` — pressed inside a cabin
- A **pluggable dispatch strategy** that picks which car serves an external request
- Cars move, stop, open/close doors

### Explicitly excluded

| Excluded | Note |
|---|---|
| Capacity / weight limits | Consciously cut — good |
| Maintenance & emergency mode | Consciously cut |
| Fire service, door sensors | Consciously cut |
| Display panels | Consciously cut |

Cutting scope deliberately (rather than forgetting it) is a positive signal, and it was done here.

---

## 3. Design Discussion — Questions Asked and Answers Given

### Q1 — Capacity constraints?

**Answer:** No capacity or weight restrictions in scope.
**Verdict:** Fine. Clean scope cut.

---

### Q2 — Is elevator assignment final, or re-evaluated?

**Scenario posed:** A request at floor 5 going DOWN is assigned to Car A, which is at floor 1 heading up with a long queue. Two seconds later Car B goes idle at floor 6. Does the request move to B?

**Answer:** Assignment is **final**. The reasoning given was that the strategy should be smart enough to anticipate this from future stops, acknowledging that not all future stops are knowable — accepted as a stated limitation.

**Verdict:** Acceptable as a scoping decision, and stating the limitation out loud is better than pretending it away.

**⚠️ But see §6.4** — the justification rests on strategy intelligence that was never implemented, and which the shipped `ElevatorController` API cannot support.

---

### Q3 — How does a moving car decide its next stop?

**Answer:** LOOK algorithm, using a min-heap and a max-heap.

**Refined over the discussion into three structures:**

| Structure | Meaning |
|---|---|
| `upFloors` | stops to serve during an upward sweep |
| `downFloors` | stops to serve during a downward sweep |
| `remainingFloors` | requests that cannot be served on the current pass |

**Worked example given by the candidate:** Car at floor 4 going UP. A request arrives from floor 2 going UP. Floor 2 is below the car, so it cannot be served on this upward pass — it goes into `remainingFloors`, to be merged back once the current sweep completes.

**Verdict:** Correct instinct, and the three-bucket idea is the right shape. The merge-back rule has a hole — see §5.

---

### Q4 — Time model: threads or ticks?

**Options put to the candidate:**

- **Option A — threads.** Each car on its own thread, `sleep()` between floors. Realistic, but shared state needs locks and tests are non-deterministic.
- **Option B — ticks.** A driver loop calls `system.step()`; each `step()` advances every car one unit. Deterministic and trivially testable.

**Answer:** **Option B**, because it makes the service testable — the same input always produces the same output. With threads, which thread wakes first depends on the OS, so output changes run to run.

**Verdict:** Correct answer, correct reasoning. This was the strongest moment of the round.

**⚠️ But see §6.1** — the submitted code uses threads.

---

### Q5 — Duplicate button presses

**Problem:** A passenger presses floor 5 twice. `std::priority_queue` stores it twice, so the car stops, opens, closes, and stops again. A priority queue also cannot answer *"is floor 5 already queued?"*

**Answer:** Switch from `priority_queue` to `std::set`.

**Verdict:** Correct. `std::set` gives dedup for free, ordered iteration in both directions, and `lower_bound` for "next stop above me." This was implemented correctly in the code:

```cpp
std::set<int> upFloors;                       // ascending  — *begin() = lowest
std::set<int, std::greater<int>> downFloors;  // descending — *begin() = highest
```

---

### Q6 — Does `ExternalButtonDispatcher` earn its existence?

**Problem:** As drawn, the dispatcher held a `scheduler` pointer and had one method that forwarded straight to it — a pass-through class.

**First answer:** It's a boundary concern; without it, every external button would hold the scheduler directly.

**Pushback:** That doesn't hold. `every button holds Scheduler*` was replaced by `every button holds Dispatcher*` — same number of edges, same coupling depth. The pointer moved; it wasn't removed.

**Second answer:** It makes sense once it owns more behaviour — for example turning the hall light off once the elevator arrives. That shouldn't be the scheduler's job.

**Verdict:** ✅ **This is the right answer.** A hall call has a *lifecycle*: created on press (light on), cleared on arrival (light off). Owning that lifecycle — plus deduplicating two people pressing UP on the same floor — is a real responsibility and justifies the class.

**Consequence noted during the round:** the dispatcher must be told when a car arrives. That means an `ElevatorController → ExternalButtonDispatcher` edge (callback / observer) that the UML did not have.

**⚠️ But see §6.3** — none of this was implemented.

---

## 4. Final Design

### 4.1 Class responsibilities

| Class | Responsibility |
|---|---|
| `ElevatorApp` | Facade. Bootstraps and wires everything; entry point for button presses. |
| `Building` / `Floor` | Physical model; floors hold hall buttons. |
| `ExternalButton` | Hall button `(floorId, direction)`. Forwards to the dispatcher. |
| `InternalButton` | Cabin button. Forwards to its own controller. |
| `ExternalButtonDispatcher` | Boundary for hall calls; intended owner of the hall-call lifecycle. |
| `ElevatorScheduler` | Holds all controllers + the active strategy; routes a request to a chosen car. |
| `ElevatorStrategy` | Interface — picks which controller serves a request. |
| `LeastBusyStrategy` | Concrete strategy — fewest queued tasks wins. |
| `ElevatorController` | **The brains.** Owns `upFloors` / `downFloors` / `remainingFloors` and runs LOOK. |
| `ElevatorCar` | Intended as a dumb object: id, current floor, door. |
| `Door` | Open/close state. |

### 4.2 Request flow

```
ExternalButton.pressButton()
        │
        ▼
ExternalButtonDispatcher.submitRequest(floorId, direction)
        │
        ▼
ElevatorScheduler.scheduleElevator(floorId, direction)
        │
        ├─► ElevatorStrategy.getElevator(controllers, floorId, direction)
        │
        ▼
ElevatorController.submitRequestExternal(floorId, direction)
        │
        ▼
   classify into upFloors / downFloors / remainingFloors
        │
        ▼
   controlElevator()  ──►  ElevatorCar.moveToFloor(...)


InternalButton.pressButton(floorId)
        │
        ▼
ElevatorController.submitRequestInternal(floorId)      ← bypasses the strategy
```

### 4.3 Enums

```cpp
enum class Direction          { UP, DOWN };              // requested direction
enum class MovementDirection  { UP, DOWN, NONE };        // car's current motion
enum class ElevatorStatus     { MOVING, IDLE };
enum class DoorStatus         { OPEN, CLOSE };
```

`MovementDirection::NONE` was added during the review — `Direction` alone had no way to express an idle car.

---

## 5. The Core Bug — Sweep Reversal

This was the most important technical issue in the round, and it was raised **three times** before it was engaged with.

### 5.1 The trace given during design review

State: car at floor **4**, direction **UP**, `upFloors = {7}`, `downFloors = {}`, `remainingFloors = {}`.

1. Request `(2, UP)` arrives. `2 < 4`, so by the stated rule it goes to `remainingFloors = {2}`.
2. Car moves 4 → 7, serves 7. `upFloors` is now empty.
3. `remainingFloors` drains into `upFloors`. Now `upFloors = {2}`.
4. Car is at **7**. Direction is **UP**. `upFloors.begin()` is **2**.

**The next stop is below the car, and the direction says UP.** The invariant *"`upFloors` holds floors above me"* is broken.

### 5.2 The offending code

```cpp
if(movDir == MovementDirection::UP){
    if(!upFloors.empty()){
        nextFloor = *upFloors.begin();
    }
    else{
        for(int floor : remainingFloors) upFloors.insert(floor);  // 2 goes into upFloors
        remainingFloors.clear();
        elevator->setDirection(MovementDirection::DOWN);
    }
}
```

Floor 2 is inserted into a set whose whole invariant is *"floors above me"*. Two iterations later the direction flips back to UP and `*upFloors.begin()` hands back 2.

### 5.3 Reproduced at runtime

Instrumented `moveToFloor` to print physical movement against recorded direction, with a hall call raced into a running car:

```
[car 0] 0 -> 4  (physical ASCEND,  state.direction=UP)
   hall call (2, UP) arrives while the car is mid-run
[car 0] 4 -> 7  (physical ASCEND,  state.direction=UP)
[car 0] 7 -> 2  (physical DESCEND, state.direction=UP)   <-- STATE LIES
```

### 5.4 Why it matters

- The passenger is served **only by accident** — `moveToFloor` teleports rather than traversing, so nothing physically breaks. Replace it with real floor-by-floor movement and the car walks the wrong way.
- The lie is **load-bearing**: `submitRequestExternal` branches on `getMovingDirection()`. Every hall call arriving during that window is classified against a direction that is false.
- The bug is **symmetric** — the same drain-and-flip pattern exists for the DOWN case.

### 5.5 Two acceptable fixes (both offered; neither taken)

**(a) Separate motion direction from service direction.**
The car at 7 travels *downward* to floor 2 without stopping for anyone, then *sweeps upward* serving up-calls. Motion is DOWN; the committed sweep is UP. Real elevators call this **deadheading**. Once these are distinct concepts, `upFloors` stops meaning "floors above me" and starts meaning **"floors to serve during the next upward sweep"** — which is what it should have meant all along, and `remainingFloors` collapses into it naturally.

**(b) Change the turnaround point.**
Instead of reversing at the bottom of `downFloors`, reverse at the minimum over **all** pending requests. The car then reaches floor 2 during the descent and the bad state never arises.

Either is acceptable. What mattered was picking one and knowing why.

---

## 6. Mistakes Made

### 6.1 ❌ Argued for ticks, implemented threads — *the biggest issue*

**Said:**
> "Option B, because it helps me test out my service. Every time I'll have the same output. Threading will depend upon the OS, which thread wakes up will change the output."

**Shipped:**

```cpp
threads.emplace_back(externalRequests, std::ref(app));
threads.emplace_back(internalRequests, std::ref(app));
```

No `step()` exists anywhere. The output is OS-scheduler dependent — precisely the property that was rejected.

**Why it costs so much:** in a machine coding round the code is the artifact that survives the interview. When it contradicts the design that was just defended for forty minutes, the interviewer can no longer tell which one represents the candidate's actual judgement.

**Fix:** implement what was argued for, or say out loud "I've changed my mind, here's why."

---

### 6.2 ❌ Claimed the bug was handled, without having written the code

**Said:** *"my code will already handle that."*

It does not — see §5.3. Making a confident claim about unwritten code, and being wrong, is the single fastest way to lose an interviewer's trust. "I'm not sure, let me think" costs nothing.

---

### 6.3 ❌ Won the dispatcher argument, then didn't build it

The hall-light lifecycle answer (§3, Q6) was correct and was accepted. But `ExternalButtonDispatcher` shipped as:

```cpp
class ExternalButtonDispatcher{
    ElevatorScheduler* scheduler;
public:
    void submitRequest(int floorId, Direction d){
        scheduler->scheduleElevator(floorId, d);
    }
};
```

No light state, no dedup, no arrival callback, no pending-request registry. The class is exactly the pass-through it was originally accused of being. The `ElevatorController → Dispatcher` arrival edge was never added, not even as a stub.

---

### 6.4 ❌ The strategy signature was fixed, but the data it needs isn't exposed

The interface was correctly widened after review:

```cpp
virtual ElevatorController* getElevator(
    std::vector<ElevatorController*>& controllers, int floorId, Direction d) = 0;
```

But `ElevatorController`'s entire public API is:

```cpp
void submitRequestInternal(int floorId);
void submitRequestExternal(int floorId, Direction d);
int  getTotalTasks();
```

There is no `getCurrentFloor()`, no `getDirection()`. A `NearestElevatorStrategy` is still unimplementable. The fix was cosmetic.

This also undermines §3 Q2: final assignment was justified by strategies being "smart enough… based on future stops," but the only shipped strategy reads a single integer count, and no strategy *can* see position or direction.

---

### 6.5 ❌ Zero observability

Not one log line in any class. `main()` prints `"Elevator system test completed."` unconditionally — a test that cannot fail.

A simulator that prints nothing cannot be reviewed by an interviewer or debugged by its author. This is also *why* §5's bug survived: with a per-move log, it would have been visible in ten seconds.

---

### 6.6 ❌ Deliverables missed

| Asked for | Delivered |
|---|---|
| Compiles and runs | ❌ missing `#include <climits>` |
| `main()` drives a deterministic scenario via `step()` | ❌ no `step()`; threads instead |
| Per-tick logs: car id, floor, direction, state | ❌ no output at all |
| ≥ 2 strategies, swappable at runtime | ❌ one strategy; `setStrategy()` never called |
| A scenario exercising the disputed case | ❌ absent |

---

### 6.7 ❌ Handed over work that was never run

The build failure was one missing header. A clean-clone build before submitting would have caught it. So would running the program once and noticing it produces no output.

**This is the single habit with the highest return on the next round.**

---

### 6.8 ❌ Dodged the hardest question three times

The sweep-reversal question was parked ("I'll discuss the whole LOOK algo separately"), then deferred again, then dismissed with "my code will already handle that."

When an interviewer returns to the same point three times, that is not nagging — that is the interviewer pointing at where the marks are. Engage with it even if the answer is incomplete.

Related: the `(5, DOWN)` scenario was asked twice before being answered, and **the reasoning was correct** — the request belongs in `downFloors` and is served on the descent. Silence read as uncertainty and cost credit that had already been earned. Say the right answer out loud.

---

## 7. What Went Well

- **Project structure is genuinely above average.** `model/`, `controller/`, `strategy/`, `manager/`, `dispatcher/`, `enum/` — one class per header, include guards throughout. This looks like production code.
- **Correct core decomposition.** Splitting `ElevatorCar` (state) from `ElevatorController` (brains) is the right call and survived scrutiny. Many candidates never separate them.
- **Strategy pattern correctly placed** — interface + concrete implementation + `setStrategy()` on the scheduler, with a virtual destructor.
- **Right data structure instincts.** Moving from `priority_queue` to `std::set` for dedup, and the three-bucket LOOK model, both came quickly.
- **Fixed problems when told.** The strategy signature and `MovementDirection::NONE` were both closed after feedback.
- **Owned misses without defensiveness.** "These are misses while making the UML, the signature needs correction" — clean, fast, no ego.
- **Articulated Option B's justification exactly right** — determinism for testability, and named OS scheduling as the source of non-reproducibility.
- **Scope was cut consciously**, not forgotten.

---

## 8. Follow-Up Questions

Worth working through before the next round:

1. **`while(isRunning)` is a spin loop.** With no work it burns 100% of a core. In a real threaded design, what replaces it?
2. **Elevator A is chosen for a hall call at floor 5. Two seconds later A goes into maintenance.** Assignment is final — what happens to that passenger? Design a way out that doesn't require re-scheduling everything.
3. **`getTotalTasks()` returns a count under a lock.** By the time the strategy compares it against another controller's count, both are stale. Bug or acceptable? Defend the answer.
4. **Add capacity.** Which classes change? Does `ElevatorStrategy` need a new parameter, or is `ElevatorController` enough?
5. **`ElevatorStatus{MOVING, IDLE}` and `DoorStatus{OPEN, CLOSE}` are independent fields.** Enumerate the four combinations — which are illegal? (`MOVING + OPEN` is a safety violation the type system currently permits.) What would a single `State` enum or a small state machine buy you?
6. **Design `NearestElevatorStrategy`.** What must `ElevatorController` expose for it to be writable at all?
7. **Two people press UP on floor 5.** Where should the deduplication live, and what tells the dispatcher the call has been satisfied?

---

## 9. Rating: 5.5 / 10

### Positives

- Clean, professional project structure
- Correct core decomposition that held up under scrutiny
- Right data-structure instincts (`set` over `priority_queue`; three-bucket LOOK)
- Fixed the strategy signature and the `Direction::NONE` gap when told
- Owned misses quickly and without defensiveness
- Articulated *why* Option B, in exactly the right terms

### Negatives

- **Implemented the opposite of the design that was defended** — threads instead of ticks
- **Missed 5 of 5 explicit deliverables**
- **Dodged the hardest question three times**, then asserted the code handled it — it doesn't
- **Zero observability** — a simulator that prints nothing can't be reviewed or debugged
- **Won the dispatcher argument and built none of it**
- Fixed the strategy signature but left the controller unable to supply what strategies need
- Handed over code that was never built or run

### Blunt version

The **design conversation** was around a **7**. The **code** was around a **4**.

In a real round the code is the artifact that survives the interview, and this code contradicts the design it was supposed to implement. Close that gap and this is a comfortable hire.

### The one habit to fix

**Run your code before you hand it over — and when an interviewer pushes on the same point three times, that's where the marks are.**

---

## 10. Checklist for Next Time

- [ ] Clean-clone build before submitting. Every time.
- [ ] Run it once. Read the output. If there is no output, that's the bug.
- [ ] Log every state transition — id, floor, direction, state.
- [ ] Implement the design that was defended, or announce the change of mind.
- [ ] Never claim unwritten code handles a case.
- [ ] Mentally execute one full request end-to-end through the UML before drawing the last box. Both broken signatures would have surfaced.
- [ ] When a class is justified by a responsibility, give it that responsibility.
- [ ] Answer the scenario asked, out loud, even when the answer feels obvious.
- [ ] `-Wall -Wextra` clean.
- [ ] Ship the number of strategies that were asked for.
