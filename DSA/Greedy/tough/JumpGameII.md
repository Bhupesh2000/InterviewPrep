/*
Assignment 8 Q8
https://leetcode.com/problems/jump-game-ii/

You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].
Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:
0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].

Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
 
Constraints:
1 <= nums.length <= 10^4
0 <= nums[i] <= 1000
It's guaranteed that you can reach nums[n - 1].
*/

Approach 1 - using plain recursion - checking for all the indices and then its possibilities
TC - O(N^N), SC - O(N) -> recursibe stac

Approach 2 - bettering the recursion approach by using 2-D dp.
TC - O(N^2), SC - O(N^2)

Approach 3 - using a range concept. keeping the track of how many min no. of jumps will it take to reach each element of the range. Elements in each range will have same number of min jumps

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2) return n - 1;

        int l = 0, r = 0;
        int jumps = 0;
        while(l < n){
            int maxI = r;
            while(l < n && l <= r){
                maxI = max(maxI, nums[l] + l);
                l ++;
            }
            r = maxI;
            jumps ++;
            if(r >= n - 1) break;
        }
        return jumps;
    }
};

TC - O(N), SC - O(1)