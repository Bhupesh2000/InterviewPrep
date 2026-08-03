/*
https://www.naukri.com/code360/problems/unbounded-knapsack_1215029?leftPanelTabValue=PROBLEM

You are given ‘n’ items with certain ‘profit’ and ‘weight’ and a knapsack with weight capacity ‘w’.
You need to fill the knapsack with the items in such a way that you get the maximum profit. You are allowed to take one item multiple times.

Example:
Input: 
'n' = 3, 'w' = 10, 
'profit' = [5, 11, 13]
'weight' = [2, 4, 6]
Output: 27
Explanation:
We can fill the knapsack as:
1 item of weight 6 and 1 item of weight 4.
1 item of weight 6 and 2 items of weight 2.
2 items of weight 4 and 1 item of weight 2.
5 items of weight 2.
The maximum profit will be from case 3 = 11 + 11 + 5 = 27. Therefore maximum profit = 27.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1:
3 15
7 2 4
5 10 20
Expected Answer:
21
Output on console:
21
Explanation of Sample Input 1
The given knapsack capacity is 15. We can fill the knapsack as [1, 1, 1] giving us profit 21 and as [1,2] giving us profit 9. Thus maximum profit will be 21.
Sample Input 2
2 3
6 12
4 17
Expected Answer:
0
Output on console:
0
Explanation of Sample Input 2:
We can clearly see that no item has weight less than knapsack capacity. Therefore we can not fill knapsack with any item.
Expected Time Complexity:
Try to solve this in O(n*w).
Constraints
1 <= n <= 10^3
1 <= w <= 10^3
1 <= profit[i] , weight[i] <= 10^8
*/

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight, int ind, vector<vector<int>>& dp){
    if(w == 0) return 0;
    if(ind == 0){
        int a = w / weight[0];
        return profit[0] * a;
    }
    if(dp[ind][w] != -1) return dp[ind][w];
    int notPick = unboundedKnapsack(n, w, profit, weight, ind - 1, dp);
    int pick = 0;
    if(w >= weight[ind]) pick = unboundedKnapsack(n, w - weight[ind], profit, weight, ind, dp) + profit[ind];
    return dp[ind][w] = max(pick, notPick);
}
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n, vector<int>(w + 1, -1));
    return unboundedKnapsack(n, w, profit, weight, n - 1, dp);
}

Other approaches - recursion, dp and dp with space optmisation