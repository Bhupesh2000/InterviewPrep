/*
https://leetcode.com/problems/coin-change-ii/description/

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
You may assume that you have an infinite number of each kind of coin.
The answer is guaranteed to fit into a signed 32-bit integer.

Example 1:
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:
Input: amount = 10, coins = [10]
Output: 1
 
Constraints:
1 <= coins.length <= 300
1 <= coins[i] <= 5000
All the values of coins are unique.
0 <= amount <= 5000
*/

Approach 1 - Recursion
class Solution {
    int change(int amount, vector<int>& coins, int ind){
        if(amount == 0) return 1;
        if(ind == 0){
            if(amount % coins[ind] == 0) return 1;
            return 0;
        }
        int notPick = change(amount, coins, ind - 1);
        int pick = 0;
        if(amount >= coins[ind]) pick = change(amount - coins[ind], coins, ind);
        return notPick + pick;
    }
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        return change(amount, coins, n - 1);
    }
};
TC - >O(2^n), SC - >O(n)

Approach 2 - Memoization
class Solution {
    int change(int amount, vector<int>& coins, int ind, vector<vector<int>>& dp){
        if(amount == 0) return 1;
        if(ind == 0){
            if(amount % coins[ind] == 0) return 1;
            return 0;
        }
        if(dp[ind][amount] != -1) return dp[ind][amount];
        int notPick = change(amount, coins, ind - 1, dp);
        int pick = 0;
        if(amount >= coins[ind]) pick = change(amount - coins[ind], coins, ind, dp);
        return dp[ind][amount] = notPick + pick;
    }
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        return change(amount, coins, n - 1, dp);
    }
};
TC - O(n * amount), SC - O(n * amount)

Approach 3 - DP
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        /// ***** good edge case
        int g = 0; 
        for (int c : coins) g = std::gcd(g, c);
        if (amount % g != 0) return 0;

        vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));
        for(int i = 0; i < n; i++) dp[i][0] = 1;
        for(int i = 0; i <= amount; i++){
            dp[0][i] = (i % coins[0] == 0) ? 1 : 0; 
        }
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= amount; j++){
                long long notPick = dp[i - 1][j];
                long long pick = 0;
                if(j >= coins[i]) pick = dp[i][j - coins[i]];
                dp[i][j] = notPick + pick;
            }
        }
        return (int) dp[n - 1][amount];
    }
};
