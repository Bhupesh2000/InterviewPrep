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
    Each operation check if it can perform k number of tasks or not

    For each mid (candidate number of tasks):

        Use deque to keep tasks that can potentially be assigned (within boosted worker capability)

        Consider only k strongest workers and k smallest task

        For each worker:

        push all the tasks that can be done by this worker with pill
        check if the first task can be performed by the worker without pill and complete that
        if not, complete the hardest task that can be fulfilled by this worker with pill(if pill is available)


class Solution {
public:
    bool canFinish(vector<int>& tasks, vector<int>& workers, int p, int strength, int k){
        deque<int> dq;
        int i = 0;

        for(int j = workers.size() - k; j < workers.size(); j++){
            int w = workers[j];
            
            //
            while(i < k && tasks[i] <= w + strength){
                dq.push_back(tasks[i]);
                i ++;
            }

            if(dq.empty()) return false;

            if(dq.front() <= w) dq.pop_front();
            else{
                if(p == 0) return false;
                p --;
                dq.pop_back();
            }
        }

        return dq.empty();
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

