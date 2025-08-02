/*
Assignment 10 Q8
https://www.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1

Given an array arr[] containing both positive and negative integers, the task is to find the length of the longest subarray with a sum equals to 0.
Note: A subarray is a contiguous part of an array, formed by selecting one or more consecutive elements while maintaining their original order.

Examples:
Input: arr[] = [15, -2, 2, -8, 1, 7, 10, 23]
Output: 5
Explanation: The longest subarray with sum equals to 0 is [-2, 2, -8, 1, 7].
Input: arr[] = [2, 10, 4]
Output: 0
Explanation: There is no subarray with a sum of 0.
Input: arr[] = [1, 0, -4, 3, 1, 0]
Output: 5
Explanation: The longest subarray with sum equals to 0 is [0, -4, 3, 1, 0]
Constraints:
1 ≤ arr.size() ≤ 10^6
−10^3 ≤ arr[i] ≤ 10^3
*/

Approach 1 - make all subarrays and check for largest subarray with sum 0

Approach 2 - use hashmap
class Solution {
  public:
    int maxLength(vector<int>& arr) {
        // code here
        int currSum = 0;
        int ans = 0;
        unordered_map<int, int> freq;
        for(int i = 0; i < arr.size(); i++){
            currSum += arr[i];
            if(currSum == 0) ans = i + 1;
            if(freq.count(currSum) > 0) ans = max(ans, i - freq[currSum]);
            else freq[currSum] = i;
        }
        return ans;
    }
};
TC - O(N), SC - O(N)