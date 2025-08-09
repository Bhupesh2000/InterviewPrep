1. The Find operation
Goal: figure out which set an element belongs to.
How: follow the “parent” links up the tree until you reach the root (a node that’s its own parent).
Result: the root is the identifier of the set.
Example:
If 4 → 2 → 1 (1 is root), then find(4) returns 1.

2. The Union operation
Goal: merge the sets containing two elements.
How:
    Find the roots of both elements using find.
    Make one root point to the other (attach one tree to the other).
    Optionally use by size or by rank so the smaller/shallow tree gets attached to the bigger/shallow one.

Why they matter:
find and union are the core of disjoint set data structures. Together, they let you keep track of which items are in the same group without having to rebuild the groups from scratch each time.

Disjoint union by size and by rank are heuristics in the disjoint set (union–find) data structure.
By size: always attach the smaller set’s root to the larger set’s root.
By rank: attach the root with smaller “rank” (approximate tree height) to the one with larger rank.
Goal: keep the tree shallow so find and union operations are near-constant time.
Use case: algorithms that repeatedly group elements into sets, like Kruskal’s MST algorithm, network connectivity checks, or tracking components in dynamic graphs.

