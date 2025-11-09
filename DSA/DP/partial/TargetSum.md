/*
Assignment 12 Q7
https://leetcode.com/problems/target-sum/

You are given an integer array nums and an integer target.
You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.
For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target.

Example 1:
Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
Example 2:
Input: nums = [1], target = 1
Output: 1
*/

static const int Mod = pow(10, 9) + 7;
class Solution {
    int findWays(vector<int>& arr, int k, int n)
    {
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));
        for(int i = 0; i < n; i++) dp[i][0] = 1;
        if (arr[0] == 0) {
            dp[0][0] = 2 % Mod;                  
        } else {
            dp[0][0] = 1;                        
            if (arr[0] <= k) dp[0][arr[0]] = 1;
        }
        for(int i = 1; i < n; i++){
            for(int j = 0; j <= k; j++){
                int notPick = dp[i - 1][j];
                int pick = 0;
                if(j >= arr[i]) pick = dp[i - 1][j - arr[i]];
                dp[i][j] = (pick % Mod + notPick % Mod) % Mod;
            }
        }
        return dp[n - 1][k];
    }

    int countPartitions(int n, int d, vector<int> &arr) {
        int totalSum = 0;
        for(int i = 0; i < n; i++) totalSum += arr[i];
        int target = totalSum - d;
        if(target < 0 || target % 2 != 0) return 0;
        target /= 2;
        return findWays(arr, target, n);
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        return countPartitions(n, target, nums); // Basically target is |S1 - S2| = d
    }
};

*** It is same as Partitions With Given Difference