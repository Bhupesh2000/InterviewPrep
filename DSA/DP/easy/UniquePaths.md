/*
https://leetcode.com/problems/unique-paths/description/

There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The test cases are generated so that the answer will be less than or equal to 2 * 10^9.

Example 1:
Input: m = 3, n = 7
Output: 28
Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Constraints:
1 <= m, n <= 100
*/

Approach 1 - Recursion
class Solution {
    int uniquePaths(int i, int j, int x, int y){
        if(i == x && j == y) return 1;
        if(i > x || j > y) return 0;
        return uniquePaths(i + 1, j, x, y) + uniquePaths(i, j + 1, x, y);
    }
public:
    int uniquePaths(int m, int n) {
        return uniquePaths(0, 0, m - 1, n - 1);
    }
};
TC - O(2^(m * n)), SC - O(m + n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int uniquePaths(int i, int j, int x, int y, vector<vector<int>>& dp){
        if(i == x && j == y) return 1;
        if(i > x || j > y) return 0;
        if(dp[i][j] != -1) return dp[i][j];
        return dp[i][j] = uniquePaths(i + 1, j, x, y, dp) + uniquePaths(i, j + 1, x, y, dp);
    }
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return uniquePaths(0, 0, m - 1, n - 1, dp);
    }
};
TC - O(m * n), SC - O((m * n) + (m + n))

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
TC - O(m * n), SC - O(m * n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - dp with space optimisation
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> up(n, 1);
        for(int i = 1; i < m; i++){
            vector<int> curr(n, 1);
            for(int j = 1; j < n; j++){
                curr[j] = up[j] + curr[j - 1];
            }
            up = curr;
        }
        return up[n - 1];
    }
};
TC - O(m * n), SC - O(n)