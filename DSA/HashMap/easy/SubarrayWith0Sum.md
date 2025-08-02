/*
Assignment 10 Q2
https://www.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1

Given an array of integers, arr[]. Find if there is a subarray (of size at least one) with 0 sum. Return true/false depending upon whether there is a subarray present with 0-sum or not. 

Examples:
Input: arr[] = [4, 2, -3, 1, 6]
Output: true
Explanation: 2, -3, 1 is the subarray with a sum of 0.
Input: arr = [4, 2, 0, 1, 6]
Output: true
Explanation: 0 is one of the element in the array so there exist a subarray with sum 0.
Input: arr = [1, 2, -1]
Output: false

Constraints:
1 <= arr.size <= 10^4
-10^5 <= arr[i] <= 10^5
*/

Approach 1 - Using brute force, create all subarrays and check if subarray with sum 0 exists or not
TC - O(N^2), SC - O(1)

Approach 2 - 
class Solution {
  public:
    // Complete this function
    // Function to check whether there is a subarray present with 0-sum or not.
    bool subArrayExists(vector<int>& arr) {
        // Your code here
        unordered_set<int> seen;
        int currSum = 0;
        for(int i = 0; i < arr.size(); i++){
            if(arr[i] == 0) return true;
            currSum += arr[i];
            if(seen.count(currSum) > 0 || currSum == 0) return true;
            seen.insert(currSum);
        }
        return false;
    }
};

TC - O(N), SC - O(N)
