/*
Assignment 12 Q2
https://leetcode.com/problems/climbing-stairs/description/

You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Example 1:
Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:
Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Constraints:
1 <= n <= 45
*/

Approach 1 - Recursion
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
};
TC - O(2^n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int climbStairs(int n, vector<int>& dp){
        if(n <= 2) return n;
        if(dp[n] != -1) return dp[n];
        return dp[n] = climbStairs(n - 1) + climbStairs(n - 2);
    }
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, -1);
        return climbStairs(n, dp);
    }
};
Tc - O(n), SC - O(2n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - DP
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
Tc - O(n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - dp with space optimisation
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        int prev2 = 1, prev1 = 2;
        int curr;
        for(int i = 3; i <= n; i++){
            curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return curr;
    }
};
TC - O(n), SC - O(1)