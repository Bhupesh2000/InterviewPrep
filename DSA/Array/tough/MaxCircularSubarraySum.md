/*
Given an array of integers arr[] in a circular fashion. Find the maximum subarray sum that we can get if we assume the array to be circular.

Examples:
Input: arr[] = [8, -8, 9, -9, 10, -11, 12]
Output: 22
Explanation: Starting from the last element of the array, i.e, 12, and moving in a circular fashion, we have max subarray as 12, 8, -8, 9, -9, 10, which gives maximum sum as 22.

Input: arr[] = [10, -3, -4, 7, 6, 5, -4, -1]
Output: 23
Explanation: Maximum sum of the circular subarray is 23. The subarray is [7, 6, 5, -4, -1, 10].

Input: arr[] = [-1, 40, -14, 7, 6, 5, -4, -1] 
Output: 52
Explanation: Circular Subarray [7, 6, 5, -4, -1, -1, 40] has the maximum sum, which is 52.

Constraints:
1 <= arr.size() <= 105
-104 <= arr[i] <= 104
*/

class Solution {
  public:
    int circularSubarraySum(vector<int> &arr) {
        // code here
        int n = arr.size();
        int totalSum = 0, maxSum = INT_MIN, minSum = INT_MAX;
        int currMaxSum = 0, currMinSum = 0;
        
        for(int i = 0; i < n; i++){
            totalSum += arr[i];
            
            currMaxSum += arr[i];
            currMinSum += arr[i];
            
            if(currMaxSum < 0) currMaxSum = 0;
            if(currMinSum > 0) currMinSum = 0;
            
            maxSum = max(maxSum, currMaxSum);
            minSum = min(minSum, currMinSum);
        }
        
        return max(maxSum, totalSum - minSum);
    }
};