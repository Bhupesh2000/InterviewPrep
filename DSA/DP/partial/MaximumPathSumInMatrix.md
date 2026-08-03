/*
https://www.geeksforgeeks.org/problems/path-in-matrix3805/1

You are given a matrix mat[][] of size n x m where each element is a positive integer. Starting from any cell in the first row, you are allowed to move to the next row, but with specific movement constraints. From any cell (r, c) in the current row, you can move to any of the three possible positions :
(r+1, c-1) — move diagonally to the left.
(r+1, c) — move directly down.
(r+1, c+1) — move diagonally to the right.
Find the maximum sum of any path starting from any column in the first row and ending at any column in the last row, following the above movement constraints.

Examples :
Input: mat[][] = [[3, 6, 1], [2, 3, 4], [5, 5, 1]]
Output: 15
Explaination: The best path is (0, 1) -> (1, 2) -> (2, 1). It gives the maximum sum as 15.
Input: mat[][] = [[2, 1, 1], [1, 2, 2]]
Output: 4
Explaination: The best path is (0, 0) -> (1, 1). It gives the maximum sum as 4.
Input: mat[][] = [[25]]
Output: 25
Explaination: (0, 0) is the only cell in mat[][], so maximum path sum will be 25.
Constraints:
1 ≤ mat.size() ≤ 500
1 ≤ mat[i].size() ≤ 500
1 ≤ mat[i][j] ≤ 1000
*/

Approach 1 - Recursion
class Solution {
    int maximumPath(vector<vector<int>>& mat, int i, int j){
        int n = mat.size(), m = mat[0].size();
        if(i == 0) return mat[i][j];
        if(j < 0 || j >= m) return INT_MIN;
        
        int s = maximumPath(mat, i - 1, j);
        int l = maximumPath(mat, i - 1, j - 1);
        int r = maximumPath(mat, i - 1, j + 1);
        
        return max(s, max(l, r)) + mat[i][j];
    }
  public:
    int maximumPath(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int maxPath = INT_MIN;
        for(int i = 0; i < m; i++){
            maxPath = max(maxPath, maximumPath(mat, n - 1, i));
        }
        return maxPath;
    }
};
TC - O(m * 3^n), SC - (n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int maximumPath(vector<vector<int>>& mat, int i, int j, vector<vector<int>>& dp){
        int n = mat.size(), m = mat[0].size();
        if(j < 0 || j >= m) return INT_MIN;
        if(i == 0) return mat[i][j];
        
        if(dp[i][j] != -1) return dp[i][j];
        
        int s = maximumPath(mat, i - 1, j, dp);
        int l = maximumPath(mat, i - 1, j - 1, dp);
        int r = maximumPath(mat, i - 1, j + 1, dp);
        
        return dp[i][j] = max(s, max(l, r)) + mat[i][j];
    }
  public:
    int maximumPath(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int maxPath = INT_MIN;
        for(int i = 0; i < m; i++){
            dp[n - 1][i] = -1;
            maxPath = max(maxPath, maximumPath(mat, n - 1, i, dp));
        }
        return maxPath;
    }
};
TC - O(n * m + m), SC - O(n * m + n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
 