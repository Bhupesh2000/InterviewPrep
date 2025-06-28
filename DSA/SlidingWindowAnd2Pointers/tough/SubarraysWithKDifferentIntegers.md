/*
Assignment 5 - Q14
https://leetcode.com/problems/subarrays-with-k-different-integers/

Given an integer array nums and an integer k, return the number of good subarrays of nums.
A good array is an array where the number of different integers in that array is exactly k.
For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
A subarray is a contiguous part of an array.

Example 1:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

Constraints:
1 <= nums.length <= 2 * 104
1 <= nums[i], k <= nums.length
*/

class Solution {
    int subarraysWithLessThanEqualK(vector<int>& nums, int k){
        int ans = 0, n = nums.size();
        unordered_map<int,int> mp;
        int left = 0, right = 0;
        while(right < n){
            mp[nums[right]] ++;
            while(mp.size() > k){
                mp[nums[left]] --;
                if(mp[nums[left]] == 0) mp.erase(nums[left]);
                left ++;
            }
            ans += (right - left + 1);
            right ++;
        }
        return ans;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        if(nums.size() < k) return 0;
        return (subarraysWithLessThanEqualK(nums, k) - subarraysWithLessThanEqualK(nums, k - 1));
    }
};

TC - O(N), SC - O(N) -> for hashmap

Recursion approach, TC -> O(N^2), SC - O(N) -> for hashmap