/*
Assignment 6 Q15
https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/

Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1], k = 1
Output: 1

Example 2:
Input: nums = [1,2], k = 4
Output: -1

Example 3:
Input: nums = [2,-1,2], k = 3
Output: 3
 
Constraints:

1 <= nums.length <= 10^5
-10^5 <= nums[i] <= 10^5
1 <= k <= 10^9
*/

Solution 1- make all subarrays and check its sum - O(N!)

Solution 2-
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        vector<long long> currSum(nums.size(), 0);
        deque<int> dq;
        int minLength = INT_MAX;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] >= k) return 1;
            
            if(i == 0) currSum[i] = nums[i];
            else currSum[i] = currSum[i - 1] + nums[i];

            if(currSum[i] >= k){
                minLength = min(minLength, i + 1);
            }
            while(!dq.empty() && currSum[i] - currSum[dq.front()] >= k){
                minLength = min(minLength, i - dq.front());
                dq.pop_front();
            }

            while(!dq.empty() && currSum[i] <= currSum[dq.back()]){
                dq.pop_back();
            }

            dq.push_back(i);
        }
        return (minLength == INT_MAX) ? -1 : minLength;
    }
};

TC - O(N), SC - O(N)
