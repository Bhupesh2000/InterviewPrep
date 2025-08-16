/*
https://www.naukri.com/code360/problems/subset-sum-equal-to-k_1550954

You are given an array/list ‘ARR’ of ‘N’ positive integers and an integer ‘K’. Your task is to check if there exists a subset in ‘ARR’ with a sum equal to ‘K’.
Note: Return true if there exists a subset with sum equal to ‘K’. Otherwise, return false.

For Example :
If ‘ARR’ is {1,2,3,4} and ‘K’ = 4, then there exists 2 subsets with sum = 4. These are {1,3} and {4}. Hence, return true.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 5
1 <= N <= 10^3
0 <= ARR[i] <= 10^9
0 <= K <= 10^3

Time Limit: 1 sec
Sample Input 1:
2
4 5
4 3 2 1
5 4
2 5 1 6 7
Sample Output 1:
true
false
Explanation For Sample Input 1:
In example 1, ‘ARR’ is {4,3,2,1} and ‘K’ = 5. There exist 2 subsets with sum = 5. These are {4,1} and {3,2}. Hence, return true.
In example 2, ‘ARR’ is {2,5,1,6,7} and ‘K’ = 4. There are no subsets with sum = 4. Hence, return false.
Sample Input 2:
2
4 4
6 1 2 1
5 6
1 7 2 9 10
Sample Output 2:
true
false
Explanation For Sample Input 2:
In example 1, ‘ARR’ is {6,1,2,1} and ‘K’ = 4. There exist 1 subset with sum = 4. That is {1,2,1}. Hence, return true.
In example 2, ‘ARR’ is {1,7,2,9,10} and ‘K’ = 6. There are no subsets with sum = 6. Hence, return false.
*/

#include <bits/stdc++.h> 
bool subsetSumToK(int n, int k, vector<int> &arr, int ind){
    if(k == 0) return true;
    if(ind == 0) return arr[0] == k;
    bool notTake = subsetSumToK(n, k, arr, ind - 1);
    if(notTake) return true;
    bool take = false;
    if(arr[ind] <= k) take = subsetSumToK(n, k - arr[ind], arr, ind - 1);
    return take;
}
bool subsetSumToK(int n, int k, vector<int> &arr) {
    return subsetSumToK(n, k, arr, n - 1);
}
TC - O(2^n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
int subsetSumToK(int n, int k, vector<int> &arr, int ind, vector<vector<int>>& dp){
    if(k == 0) return 1;
    if(ind == 0) return arr[0] == k ? 1 : 0;
    if(dp[ind][k] != -1) return dp[ind][k];
    int notTake = subsetSumToK(n, k, arr, ind - 1, dp);
    if(notTake == 1) return dp[ind][k] = 1;
    int take = 0;
    if(arr[ind] <= k) take = subsetSumToK(n, k - arr[ind], arr, ind - 1, dp);
    return dp[ind][k] = take;
}
bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return subsetSumToK(n, k, arr, n - 1, dp) == 0 ? false : true;
}
TC - O(n * k), SC - O(n * k) + O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));
    for(int i = 0; i < n; i++) dp[i][0] = true;
    dp[0][arr[0]] = true;
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= k; j++){
            bool notTake = dp[i - 1][j];
            bool take = false;
            if(arr[i] <= j) take = dp[i - 1][j - arr[i]];
            dp[i][j] = notTake || take;
        }
    }
    return dp[n - 1][k];
}
TC - O(n * k), SC - O(n * k)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - can be space optimised to O(target)