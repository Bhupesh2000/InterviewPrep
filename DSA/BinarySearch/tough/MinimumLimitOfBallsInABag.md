/*
Assignment- 8 Q9
https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/description/

You are given an integer array nums where the ith bag contains nums[i] balls. You are also given an integer maxOperations.
You can perform the following operation at most maxOperations times:
Take any bag of balls and divide it into two new bags with a positive number of balls.
For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2 and 3 balls.
Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the operations.
Return the minimum possible penalty after performing the operations.

Example 1:
Input: nums = [9], maxOperations = 2
Output: 3
Explanation: 
- Divide the bag with 9 balls into two bags of sizes 6 and 3. [9] -> [6,3].
- Divide the bag with 6 balls into two bags of sizes 3 and 3. [6,3] -> [3,3,3].
The bag with the most number of balls has 3 balls, so your penalty is 3 and you should return 3.

Example 2:
Input: nums = [2,4,8,2], maxOperations = 4
Output: 2
Explanation:
- Divide the bag with 8 balls into two bags of sizes 4 and 4. [2,4,8,2] -> [2,4,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,4,4,4,2] -> [2,2,2,4,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,4,4,2] -> [2,2,2,2,2,4,2].
- Divide the bag with 4 balls into two bags of sizes 2 and 2. [2,2,2,2,2,4,2] -> [2,2,2,2,2,2,2,2].
The bag with the most number of balls has 2 balls, so your penalty is 2, and you should return 2.
 
Constraints:
1 <= nums.length <= 10^5
1 <= maxOperations, nums[i] <= 10^9
*/

class Solution {
    // Helper function to check if it's possible to reduce each bag to size `size` or less
    // using at most `maxOps` operations
    bool isPossible(vector<int>& nums, int size, int maxOps){
        int totalOps = 0;
        for(int num : nums){
            // Each bag with `num` balls needs (ceil(num / size) - 1) operations
            // to be split into bags of at most `size` balls
            totalOps += (int)ceil(double(num) / size) - 1;
            
            // Early return if operations exceed limit
            if(totalOps > maxOps) return false;
        }
        return true;
    }

public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int l = 1;            // Minimum possible bag size
        int r = 0;            // Maximum number of balls in any bag
        for(int num : nums) r = max(r, num);  // Set upper bound
        
        int ans = r;          // Store the minimum valid bag size

        // Binary search to find the minimum size that satisfies the condition
        while(l <= r){
            int mid = (l + r) / 2;

            // If we can make all bags of size `mid` or less using `maxOperations`
            if(isPossible(nums, mid, maxOperations)){
                ans = mid;    // Update result
                r = mid - 1;  // Try smaller size
            }
            else {
                l = mid + 1;  // Try larger size
            }
        }

        return ans;  // Return the minimum possible maximum bag size
    }
};

| Component                 | Time Complexity | Space Complexity | Explanation                                       |
| ------------------------- | --------------- | ---------------- | ------------------------------------------------- |
| `isPossible()` (per call) | O(N)            | O(1)             | Iterates over `nums` once to count operations     |
| Binary Search Iterations  | O(log M)        | —                | Where `M` = max element in `nums`                 |
| Total Time                | O(N × log M)    | O(1)             | `isPossible()` called for each binary search step |
| Overall Auxiliary Space   | —               | O(1)             | No extra space used except variables              |
