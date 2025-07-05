/*
Assignment 6 Q16
https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/

You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed integer array tasks, with the ith task requiring tasks[i] strength to complete. The strength of each worker is stored in a 0-indexed integer array workers, with the jth worker having workers[j] strength. Each worker can only be assigned to a single task and must have a strength greater than or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).

Additionally, you have pills magical pills that will increase a worker's strength by strength. You can decide which workers receive the magical pills, however, you may only give each worker at most one magical pill.

Given the 0-indexed integer arrays tasks and workers and the integers pills and strength, return the maximum number of tasks that can be completed.

Example 1:
Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
Output: 3
Explanation:
We can assign the magical pill and tasks as follows:
- Give the magical pill to worker 0.
- Assign worker 0 to task 2 (0 + 1 >= 1)
- Assign worker 1 to task 1 (3 >= 2)
- Assign worker 2 to task 0 (3 >= 3)

Example 2:
Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
Output: 1
Explanation:
We can assign the magical pill and tasks as follows:
- Give the magical pill to worker 0.
- Assign worker 0 to task 0 (0 + 5 >= 5)

Example 3:
Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
Output: 2
Explanation:
We can assign the magical pills and tasks as follows:
- Give the magical pill to worker 0 and worker 1.
- Assign worker 0 to task 0 (0 + 10 >= 10)
- Assign worker 1 to task 1 (10 + 10 >= 15)
The last pill is not given because it will not make any worker strong enough for the last task.
 
Constraints:
n == tasks.length
m == workers.length
1 <= n, m <= 5 * 10^4
0 <= pills <= m
0 <= tasks[i], workers[j], strength <= 10^9
*/

Sort both tasks and workers

Perform binary search on number of tasks to assign

    For each mid (candidate number of tasks):

        Use deque to keep tasks that can potentially be assigned (within boosted worker capability)

        Traverse from strongest workers to weakest (right to left)

        For each worker:

        Try to assign the hardest task they can do without a pill (right end)

        If not possible, try to use a pill to assign the easiest viable task (left end)

        If neither works, return false


class Solution {
public:
    // Checks if it's possible to assign `mid` tasks
    bool canFinish(vector<int>& tasks, vector<int>& workers, int pills, int strength, int mid) {
        deque<int> dq;
        int t = mid - 1;  // index in tasks
        int p = pills;

        // Add the hardest `mid` tasks into the deque (sorted in ascending)
        for (int i = mid - 1; i >= 0; --i) {
            dq.push_front(tasks[i]);
        }

        // Traverse the `mid` strongest workers (from end)
        for (int i = workers.size() - 1; i >= workers.size() - mid; --i) {
            int w = workers[i];

            // Case 1: If worker can do the hardest remaining task without pill
            if (!dq.empty() && dq.back() <= w) {
                dq.pop_back(); // assign task
            }
            // Case 2: Try using a pill if worker + strength can handle easiest remaining task
            else if (!dq.empty() && dq.front() <= w + strength) {
                dq.pop_front(); // use pill
                p--;
                if (p < 0) return false; // no pills left
            }
            // Case 3: Cannot assign this worker any task
            else {
                return false;
            }
        }

        return true; // All workers assigned a task
    }

    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());

        int low = 0, high = min((int)tasks.size(), (int)workers.size());
        int answer = 0;

        // Binary search to find maximum number of tasks that can be assigned
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canFinish(tasks, workers, pills, strength, mid)) {
                answer = mid;       // mid is valid, try more
                low = mid + 1;
            } else {
                high = mid - 1;     // mid too big, reduce
            }
        }

        return answer;
    }
};


🔍 High-Level Structure of the Code:
We are using binary search to find the maximum number of tasks (mid) that can be assigned.
For each value of mid, we check if assignment is feasible using canFinish().
Let’s denote:
n = number of tasks
m = number of workers
Let q = min(n, m) (maximum number of assignments we can try)

✅ Step-by-Step Time Complexity:
1. Sorting Tasks and Workers
sort(tasks.begin(), tasks.end());     // O(n log n)
sort(workers.begin(), workers.end()); // O(m log m)
So this is:
O(n log n + m log m) — done once

2. Binary Search on mid
We perform binary search on mid in the range [0, q]
Binary search runs in O(log q) iterations.

3. Each canFinish() Call
Within each canFinish() call:
We process mid tasks and mid workers
The operations:
Pushing mid tasks to a deque: O(mid)
Processing each of mid workers:
Each deque pop_front / pop_back = O(1)
So each canFinish() call is:
O(mid) ≈ O(q) in the worst case

🧮 Total Time Complexity

Sorting:          O(n log n + m log m)
Binary search:    O(log q)
Each check:       O(q)
Total check cost: O(q * log q)

✅ Final Time Complexity:
O(n log n + m log m + q * log q)

Since q = min(n, m), it simplifies to:
O(n log n + m log m + min(n, m) * log(min(n, m)))

📌 Space Complexity:
O(1) extra space (in-place sort)
O(q) for deque in each canFinish() call
So: O(q) auxiliary space (not counting input)

