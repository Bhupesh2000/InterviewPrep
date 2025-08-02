/*
Assignment 10 Q11
https://www.geeksforgeeks.org/problems/largest-subarray-of-0s-and-1s/1

Given an array arr of 0s and 1s. Find and return the length of the longest subarray with equal number of 0s and 1s.

Examples:
Input: arr[] = [1, 0, 1, 1, 1, 0, 0]
Output: 6
Explanation: arr[1...6] is the longest subarray with three 0s and three 1s.
Input: arr[] = [0, 0, 1, 1, 0]
Output: 4
Explnation: arr[0...3] or arr[1...4] is the longest subarray with two 0s and two 1s.
Input: arr[] = [0]
Output: 0
Explnation: There is no subarray with an equal number of 0s and 1s.
Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 1
*/

class Solution {
  public:
    int maxLen(vector<int> &arr) {
        // Your code here
        unordered_map<int, int> seen;
        int currSum = 0;
        int ans = 0;
        for(int i = 0; i < arr.size(); i++){
            currSum += (arr[i] == 0) ? -1 : 1;
            if(currSum == 0) ans = i + 1;
            if(seen.count(currSum) > 0) ans = max(ans, i - seen[currSum]);
            else seen[currSum] = i;
        }
        return ans;
    }
};
