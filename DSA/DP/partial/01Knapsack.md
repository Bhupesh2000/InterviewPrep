/*
Assignment 12 Q5
https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0

Given n items, each with a specific weight and value, and a knapsack with a capacity of W, the task is to put the items in the knapsack such that the sum of weights of the items <= W and the sum of values associated with them is maximized. 
Note: You can either place an item entirely in the bag or leave it out entirely. Also, each item is available in single quantity.

Examples :
Input: W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1] 
Output: 3
Explanation: Choose the last item, which weighs 1 unit and has a value of 3.
Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6] 
Output: 0
Explanation: Every item has a weight exceeding the knapsack's capacity (3).
Input: W = 5, val[] = [10, 40, 30, 50], wt[] = [5, 4, 2, 3] 
Output: 80
Explanation: Choose the third item (value 30, weight 2) and the last item (value 50, weight 3) for a total value of 80.
Constraints:
2 ≤ val.size() = wt.size() ≤ 10^3
1 ≤ W ≤ 10^3
1 ≤ val[i] ≤ 10^3
1 ≤ wt[i] ≤ 10^3
*/

Approach 1 - Recursion
class Solution {
    int knapsack(int W, vector<int> &val, vector<int> &wt, int n, int curr){
        if(curr >= n) return 0;
        int a = INT_MIN, b = INT_MIN;
        if(wt[curr] <= W) a = knapsack(W - wt[curr], val, wt, n, curr + 1) + val[curr];
        b = knapsack(W, val, wt, n, curr + 1);
        return max(a, b);
    }
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        int n = val.size();
        return knapsack(W, val, wt, n, 0);
    }
};
TC - O(2^n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int knapsack(int W, vector<int> &val, vector<int> &wt, int n, int curr, vector<vector<int>>& dp){
        if(curr >= n) return 0;
        if(dp[curr][W] != -1) return dp[curr][W];
        int skip = knapsack(W, val, wt, n, curr + 1, dp);
        int take = 0;
        if(wt[curr] <= W) take = knapsack(W - wt[curr], val, wt, n, curr + 1, dp) + val[curr];
        return dp[curr][W] = max(skip, take);
    }
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1, -1));
        return knapsack(W, val, wt, n, 0, dp);
    }
};
Tc - O(N * W), SC - O(N * W + N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - DP
class Solution {
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        // code here
        int n = val.size();
        vector<vector<int>> dp(n, vector<int>(W + 1));
        for(int i = 0; i < n; i++) dp[i][0] = 0;
        for(int i = 0; i <= W; i++){
            if(i >= wt[0]) dp[0][i] = val[0];
            else dp[0][i] = 0;
        }
        for(int i = 1; i < n; i++){
            for(int j = 1; j <= W; j++){
                int skip = dp[i - 1][j];
                int take = 0;
                if(wt[i] <= j) take = dp[i - 1][j - wt[i]] + val[i];
                dp[i][j] = max(skip, take);
            }
        }
        return dp[n - 1][W];
    }
};
Tc - O(N * W), SC - O(N * W)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - DP with space optimisation
class Solution {
  public:
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        int n = val.size();
        if(n == 1){
            if(W >= wt[0]) return val[0];
            else return 0;
        }
        vector<int> prev(W + 1);
        for(int i = 0; i <= W; i++){
            if(i >= wt[0]) prev[i] = val[0];
            else prev[i] = 0;
        }
        for(int i = 1; i < n; i++){
            vector<int> curr(W + 1, 0);
            for(int j = 1; j <= W; j++){
                int skip = prev[j];
                int take = (wt[i] <= j) ? prev[j - wt[i]] + val[i] : 0;
                curr[j] = max(skip, take);
            }
            prev = curr;
        }
        return prev[W];
    }
};
TC - O(N * W), SC - O(W)