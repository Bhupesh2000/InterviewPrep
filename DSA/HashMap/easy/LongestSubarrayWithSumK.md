/*
Assignment 10 Q10
https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1

Given an array arr[] containing integers and an integer k, your task is to find the length of the longest subarray where the sum of its elements is equal to the given value k. If there is no subarray with sum equal to k, return 0.

Examples:
Input: arr[] = [10, 5, 2, 7, 1, -10], k = 15
Output: 6
Explanation: Subarrays with sum = 15 are [5, 2, 7, 1], [10, 5] and [10, 5, 2, 7, 1, -10]. The length of the longest subarray with a sum of 15 is 6.
Input: arr[] = [-5, 8, -14, 2, 4, 12], k = -5
Output: 5
Explanation: Only subarray with sum = -5 is [-5, 8, -14, 2, 4] of length 5.
Input: arr[] = [10, -10, 20, 30], k = 5
Output: 0
Explanation: No subarray with sum = 5 is present in arr[].

Constraints:
1 ≤ arr.size() ≤ 10^5
-10^4 ≤ arr[i] ≤ 10^4
-10^9 ≤ k ≤ 10^9
*/

class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        // code here
        int currSum = 0;
        int ans = 0;
        unordered_map<int, int> freq;
        for(int i = 0; i < arr.size(); i++){
            currSum += arr[i];
            if(currSum == k) ans = i + 1;
            if(freq.count(currSum - k) > 0) ans = max(ans, i - freq[currSum - k]);
            if(freq.count(currSum) == 0)freq[currSum] = i;
        }
        return ans;
    }
};