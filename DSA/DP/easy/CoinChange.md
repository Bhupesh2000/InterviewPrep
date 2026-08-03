/*
https://leetcode.com/problems/coin-change/description/

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Example 1:
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:
Input: coins = [2], amount = 3
Output: -1
Example 3:
Input: coins = [1], amount = 0
Output: 0
 
Constraints:
1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4
*/

Approach 1 - Recursion
class Solution {
    int coinChange(vector<int>& coins, int amount, int ind){
        if(amount == 0) return 0;
        if(ind == 0){
            if(amount % coins[ind] == 0) return amount / coins[ind];
            else return -1;
        }
        int notPick = coinChange(coins, amount, ind - 1);
        int pick = -1;
        if(amount >= coins[ind]) pick = coinChange(coins, amount - coins[ind], ind);
        if(pick == -1 && notPick == -1) return -1;
        if(pick == -1 || notPick == -1) return (pick == -1) ? notPick : pick + 1;
        return (pick + 1) > notPick ? notPick : pick + 1;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        return coinChange(coins, amount, n - 1);
    }
};
TC - >>> O(2^n)(just say exponential), SC - >O(n), can go upto max of O(target)(reducing by 1 each time)

Approach 2 - Memoization
class Solution {
    int coinChange(vector<int>& coins, int amount, int ind, vector<vector<int>>& dp){
        if(amount == 0) return 0;
        if(ind == 0){
            if(amount % coins[ind] == 0) return amount / coins[ind];
            else return -1;
        }
        if(dp[ind][amount] != -2) return dp[ind][amount];
        int notPick = coinChange(coins, amount, ind - 1, dp);
        int pick = -1;
        if(amount >= coins[ind]) pick = coinChange(coins, amount - coins[ind], ind, dp);
        if(pick == -1 && notPick == -1) return dp[ind][amount] = -1;
        if(pick == -1 || notPick == -1) return dp[ind][amount] = (pick == -1) ? notPick : pick + 1;
        return dp[ind][amount] = (pick + 1) > notPick ? notPick : pick + 1;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -2));
        return coinChange(coins, amount, n - 1, dp);
    }
};
TC - O(n * amount), SC - O(n * amount + n)

Approach 3 - Recursion
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1));
        for(int i = 0; i < n; i++) dp[i][0] = 0;
        for(int i = 1; i <= amount; i++){
            if(i % coins[0] == 0) dp[0][i] = i / coins[0];
            else dp[0][i] = -1;
        }
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= amount; j++){
                int notPick = dp[i - 1][j];
                int pick = -1;
                if(j >= coins[i]) pick = dp[i][j - coins[i]];
                if(pick == -1 && notPick == -1) dp[i][j] = -1;
                else if(pick == -1 || notPick == -1) dp[i][j] = (pick == -1) ? notPick : pick + 1;
                else dp[i][j] = (pick + 1) > notPick ? notPick : pick + 1;
            }
        }
        return dp[n - 1][amount];
    }
};
TC - O(n * amount), SC - O(n * amount)