# Vending Machine — LLD / Machine Coding Review

**Level:** SDE-2 · **Language:** C++17 · **Format:** Design discussion → State diagram → UML → Working code → Follow-ups

**Final rating: 7 / 10**

---

## 1. Problem

Design a vending machine that dispenses items to a customer. The machine holds items in shelves. A user inserts cash, selects products, and the machine either dispenses the items with change, or refunds the money if it cannot fulfil the request. An operator can restock items and refill the cash float.

---

## 2. Scope Agreed Up Front

| Decision | Choice | Rationale |
|---|---|---|
| Concurrency | Single user at a time | Mirrors a physical machine |
| Admin auth | Out of scope | Deliberate simplification |
| Selection granularity | By `shelfId` | Avoids ambiguity when two shelves hold the same product |
| Shelf contents | N units of exactly one product | Matches real hardware |
| Shelf count | 9 (intended) | See Bug #1 — actual code creates 8 |
| Payment | Cash only (notes/coins) | Card out of scope |
| Insert style | One denomination + qty per call, repeatable | Drives the `AddMoney` self-loop |
| Price ownership | On `Item`, not `Shelf` | Shelf is a container; the product is what is sold |
| No exact change | Refund the full amount, return to Idle | Simpler than blocking selections up front |
| Cancel | Allowed in AddMoney and ItemSelection; not after confirm | Explicit point of no return |
| Multi-item | Supported — cart-style, all-or-nothing | Went beyond the typical single-item machine |

### Scope trade-offs flagged during discussion

- **Price on `Item`.** Defensible for a single machine. The counter-argument is that the same product carries different prices in different machines/locations, so price is really a property of *this machine's offering* of the product. Fine as scoped; would need revisiting for a multi-machine design.
- **Insufficient money → full refund.** The weakest UX decision in the design. A user who inserts ₹20 and picks a ₹30 item gets ejected instead of being asked for ₹10 more. An `ItemSelection → AddMoney` top-up edge is cheap and strictly better. Accepted as a deliberate simplification, but it should be named as one.
- **Change checked after selection, not before.** Real machines grey out selections they cannot make change for. Post-hoc validation is acceptable but is the less user-friendly ordering.

---

## 3. State Machine

```
                  ┌──────────────────┐         ┌──────────────┐
                  │ RefillInventory  │◄──┐  ┌─►│  RefillCash  │
                  │  (self-loop)     │   │  │  │ (self-loop)  │
                  └────────┬─────────┘   │  │  └──────┬───────┘
              addInventory │   confirm() │  │ refillCash  │ confirm()
                           ▼             │  │             ▼
                        ┌────────────────┴──┴────────────────┐
              ┌────────►│               IDLE                 │
              │         └────────────────┬───────────────────┘
              │                          │ insertCash()
              │                          ▼
              │   cancel()      ┌──────────────────┐
              ├─────────────────┤    ADD MONEY     │◄─┐ insertCash()
              │  + refund       └────────┬─────────┘──┘
              │                          │ selectItem()
              │                          ▼
              │   cancel / item unavail  ┌──────────────────┐
              ├──────────────────────────┤  ITEM SELECTION  │◄─┐ selectItem()
              │   change unavail         └────────┬─────────┘──┘
              │   insufficient money              │ confirm()
              │        + refund                   ▼
              │                          ┌──────────────────┐
              └──────────────────────────┤   DISPENSING     │
                    item + change        └──────────────────┘
```

`Dispensing` is an internal state — entered and exited synchronously by `confirm()`, never externally driven.

---

## 4. Class Design

```
VendingMachine
  ├── Inventory*   inventory     unordered_map<int, Shelf*>, unordered_map<int, Item*>
  ├── CashHolder*  cashHolder    unordered_map<Currency,int> + ChangeHandler chain
  ├── Purchase*    purchase      in-flight transaction (selected items + staged cash)
  └── State*       currState     Flyweight, resolved via StateFactory

State  (abstract, default impls reject with a log)
  ├── IdleState              ├── SelectItemState        ├── RefillCashState
  ├── AddMoneyState          ├── DispensingState        └── RefillInventoryState

ChangeHandler  (Chain of Responsibility)
  └── Denominator(HUNDRED) → FIFTY → TWENTY → TEN → FIVE → TWO → ONE
```

### Patterns used

| Pattern | Where | Verdict |
|---|---|---|
| **State** | `State` + 6 concrete states | Correct. Base class implements all 8 operations as rejections; subclasses override only what is legal. Avoids ~40 stub methods. |
| **Flyweight** | `StateFactory` function-local statics | Correct *because* states hold no data — everything arrives via the `VendingMachine*` parameter. |
| **Factory** | `StateFactory` | Also the mechanism that breaks the header cycle. |
| **Chain of Responsibility** | `ChangeHandler` | Works, but over-engineered — see Follow-up #3. |

---

## 5. What Was Done Well

**Change-making is correct, and correct for the right reason.** Greedy is the default answer and it breaks on non-canonical denomination sets (600 from `{500×1, 200×3}` — greedy takes the 500 and strands 100). The submitted code does exhaustive backtracking with proper undo, and the failure invariant holds: a `handle()` that returns `false` leaves the `change` map untouched, verified by inspection and by test.

Verified behaviour:
- Float `{20×3}`, need 45 back → correctly refused
- Float `{20×3, 5×1}`, need 45 back → correctly produced 20+20+5

**The escrow model.** Staged cash never enters `CashHolder` until `completeSale`. Refund is therefore correct by construction — there is nothing to unwind. A pleasant consequence: because `handle()` reads `machineCash + staged`, the customer's own note can be returned as change. Verified — empty float, pay 10+5 for a ₹5 item, the 10 comes back. That is real-machine behaviour, obtained for free from the design.

**Header cycle resolution.** `State.h` forward-declares `VendingMachine`; `StateFactory.h` declares bodiless statics; `StateImpl.h` is the single assembly point where both types are complete. This is the problem that derails most C++ machine-coding submissions, handled cleanly.

**Two-phase commit ordering** in `DispensingState`: settle cash first, pull stock second, so the irreversible step happens last — with the reasoning written into a comment.

**`Purchase` as a first-class object.** Most candidates smear staged cash and selected items directly onto the machine. Isolating them makes `reset()` the single cleanup path and is the foundation any concurrency retrofit would build on.

**Re-validation at `confirm()`** rather than trusting the state captured at selection time.

---

## 6. Bugs Found

### Bug 1 — Eight shelves, not nine

```cpp
Inventory(){
    for(int i = 1; i < 9; i++)      // creates shelves 1..8
        shelves[i] = new Shelf(i);
}
```

Shelf 9 does not exist. Compounded by Bug 2, `addInventory(9, ...)` fails **silently**. The count was also supposed to be a constructor parameter, not a hardcoded literal.

### Bug 2 — `IdleState` swallows every failure *(most significant)*

The maintenance states check return values and log. `IdleState`, the entry point into those states, ignores all three:

```cpp
void addInventory(VendingMachine* machine, int shelfId, int itemId, int qty) override {
    machine->getInventory()->refillItem(shelfId, itemId, qty);   // return value dropped
    machine->setState(StateFactory::refillInventory());          // transitions regardless
}
```

Observed failures:

| Call | Expected | Actual |
|---|---|---|
| `addInventory(9, 101, 5)` | error — no such shelf | silent success, transitions |
| `addInventory(77, 101, 3)` | error — no such shelf | silent success, transitions |
| `addInventory(1, 102, 3)` on a shelf holding item 101 | error | silent no-op *(logs correctly if called from `RefillInventoryState`)* |
| `insertCash(TEN, -5)` | rejected | transitions to `AddMoneyState` with ₹0 staged |

**The same operation behaves differently depending on which state invoked it.** This is the classic State-pattern trap — entry transitions and self-loops drifting apart. The fix is the one already applied elsewhere in this codebase: funnel both through a shared protected helper, exactly like `State::addSelection`.

### Bug 3 — Unpriceable shelf is treated as free

```cpp
int price = inv->getPrice(it.first);
if(price != -1) total += price * it.second;   // silently skipped
```

Currently shielded by the preceding `hasStock` check, but that is an invisible coupling. The root cause is `-1` overloaded to mean both "no such shelf" and "empty shelf". Use `std::optional<int>` and fail loudly.

### Bug 4 — Smaller issues

- `const int getId()` — top-level const on a return type is ignored by the compiler (`-Wignored-qualifiers`). The intent was `int getId() const`. **No getter in the codebase is a const member function**, so nothing can be held by const reference.
- `Shelf::hasStock(int qty)` — parameter shadows the member `qty`.
- `CashHolder::remove` can drive counts negative; no guard. Unreachable today, but it is public API.
- `getSelectedItems()` / `getStagedMoney()` return `unordered_map` **by value**. `SelectItemState::confirm` copies two maps per call for no reason.
- Raw `new`/`delete` throughout, with ownership split: `Inventory` owns `Shelf`, `main` owns `Item`. `unique_ptr` is expected at this level.
- `regsiterItem` — typo in a public method name.

---

## 7. The Central Design Critique

**Validation runs twice; `DispensingState` earns nothing.**

`SelectItemState::confirm()` checks stock, checks payment sufficiency, and calls `returnChange()` to probe that change is makeable. It then sets the state to `Dispensing` and calls `machine->confirm()` — which re-checks stock and **recomputes the entire change breakdown** via `completeSale()`.

Single-threaded, nothing can change between those two points. So:

1. The second validation pass is dead code.
2. The most expensive operation in the system runs **twice per sale**.
3. `Dispensing` is pure indirection — it is driven synchronously by the state that just finished validating everything it re-validates.

**Resolution: pick one owner.** Either `SelectItemState::confirm` is a pure gate and `DispensingState` commits blindly, or `SelectItemState` merely transitions and `Dispensing` owns all validation. The current design pays the cost of a check-then-act split without collecting any of the benefit.

---

## 8. Follow-Up Questions

### Q1 — Where do the locks go? *(partially correct)*

**Answered:** locks on `Inventory` and `CashHolder`; one `Purchase` per customer.

**Gaps:**

Per-component locks make each *component* atomic but not the *sale*. A sale spans both components, so cash can commit and stock can then fail with no rollback path. The transaction must be the critical section, not the components. Two locks acquired in unspecified order is also a deadlock risk.

More importantly: **`currState` is a single field on `VendingMachine`.** Per-customer `Purchase` objects do not help while everyone shares one state pointer — customer A's `confirm()` moves the machine to `Dispensing` underneath customer B. The unit that must be per-customer is a **`Session { State*, Purchase }`**, with the machine becoming a holder of sessions.

Also legitimate, if stated deliberately: a physical vending machine *is* single-user, so "the machine is one big mutex" is a valid answer — it just has to be the chosen answer rather than the accidental one.

### Q2 — The `returnChange` / `completeSale` TOCTOU *(correct — strongest answer)*

**Answered:** under concurrency the probe and the commit can disagree, or the probe can succeed where the commit fails. Close it by **reserving** the change computed during the probe against the `Purchase`, and releasing it at `completeSale`.

That is the right instinct. Two omissions: **stock needs reserving too**, not just change; and every reservation needs a release path — on cancel, on failure, and **on timeout**, or an abandoned session locks inventory permanently.

### Q3 — Why Chain of Responsibility over a sorted vector? *(incorrect reasoning)*

**Answered:** inserting a new denomination mid-order is cheaper in a chain than in a sorted vector.

This does not hold. Inserting mid-chain requires walking the chain to find the insertion point — O(n), the same as `vector::insert`'s memmove. With seven denominations, both are free. The chain buys nothing on that axis.

**The honest defence of CoR here:** it expresses the backtracking recursion naturally, and it allows per-denomination rules ("never dispense more than 5 of these", "this hopper is jammed"). Absent those requirements, `solve(idx, amount)` over a sorted vector is the identical algorithm with less allocation and less pointer-chasing.

*Interview note: being willing to say "this is over-engineered" about your own design reads better than defending it with an argument that does not survive scrutiny.*

### Q4 — Worst-case complexity of `handle()`? *(not answered)*

`handle()` loops `count` from `maxToBeUsed` down to 0, recursing at every value. That is a branching search with worst case ≈ **∏(cᵢ + 1)** over denominations — **exponential**.

Demonstrated by removing `ONE` and `FIVE` from the float so every remaining denomination is even, then requesting an odd (therefore unmakeable) amount, which forces exhaustion of the whole search space:

```
float = {100×20, 50×20, 20×20, 10×20, 2×60}

amount  201 -> IMPOSSIBLE    0 ms
amount  501 -> IMPOSSIBLE    2 ms
amount  999 -> IMPOSSIBLE   21 ms
amount 1501 -> IMPOSSIBLE   58 ms
```

Raising each note count to 200 and requesting 6001 **did not terminate**. A vending machine that hangs because someone paid with a large note against an awkward float.

**Fix:** memoize on `(denominationIndex, remainingAmount)`. That collapses the search to **O(k × amount)** states — bounded and fast, with identical correctness. This matters doubly because the solver currently runs twice per sale (Section 7).

### Q5 — Why are the `StateFactory` statics safe? *(not answered)*

Two parts:

1. **Initialization.** C++11 guarantees thread-safe initialization of function-local statics ("magic statics"), so concurrent first calls are safe.
2. **Sharing.** They are safe to share across every machine because **the states are stateless** — no data members; everything arrives through the `VendingMachine*` parameter. This is the Flyweight discipline.

It breaks the moment anyone adds a data member to a state class, at which point all machines silently share it. Worth an explicit comment guarding the invariant.

---

## 9. Scorecard

| Area | Assessment |
|---|---|
| Requirements gathering | **Strong** — pushed back with reasons, conceded without ego |
| State modelling | **Strong** — complete, with self-loops and failure edges drawn |
| Class design | **Strong** — `Purchase` isolation and Flyweight states are above bar |
| Pattern selection | **Good** — all four justified; CoR over-applied |
| Core algorithm | **Strong** — anticipated non-canonical denominations unprompted |
| Complexity analysis | **Weak** — unbounded exponential search, unnoticed |
| C++ rigour | **Weak** — no const-correctness, raw owning pointers, maps by value |
| Edge-case handling | **Mixed** — self-loops guarded well, entry transitions not at all |
| Concurrency reasoning | **Mixed** — reservation instinct is right; session/state sharing missed |
| Code hygiene | **Good** — compiles clean, comments explain *why*, no ASan/UBSan findings |

---

## 10. Priority Fix List

1. **`IdleState` must respect return values** — route entry transitions and self-loops through one shared helper *(correctness, and the single highest-value fix)*
2. **Memoize `ChangeHandler::handle`** on `(index, amount)` *(removes a hang)*
3. **Collapse the duplicated validation** between `SelectItemState` and `DispensingState` — pick one owner *(halves the cost of the most expensive operation)*
4. `for(i = 1; i < 9)` → `i <= shelfCount`, taken as a constructor parameter *(off-by-one)*
5. Replace the `-1` price sentinel with `std::optional<int>` *(removes a latent free-item path)*
6. Const-correct the getters; return containers by `const&` *(C++ hygiene)*
7. `unique_ptr` for `Shelf` and `Item`; consolidate ownership in `Inventory` *(memory safety)*
8. Add an `ItemSelection → AddMoney` top-up edge *(UX; removes the worst behaviour in the spec)*
9. Fix `regsiterItem`; rename the `qty` shadow in `Shelf::hasStock`

---

## 11. Verdict

**7 / 10.**

Working, well-structured code with correctly-chosen patterns and a core algorithm that is right for a reason most candidates miss. The escrow model and the header-cycle resolution both show judgement beyond the immediate problem.

Held back by an entry-transition validation gap that makes the same operation behave two different ways, a duplicated validation path that renders one state inert, an unbounded search that can hang the machine, and thin answers on complexity and concurrency depth. Those last two are precisely the axes that separate SDE-2 from SDE-1 — the design instincts are already at level; the analytical rigour behind them is not yet.