/*
https://leetcode.com/problems/cherry-pickup-ii/description/

You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.
You have two robots that can collect cherries for you:
Robot #1 is located at the top-left corner (0, 0), and
Robot #2 is located at the top-right corner (0, cols - 1).
Return the maximum number of cherries collection using both robots by following the rules below:
From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
When both robots stay in the same cell, only one takes the cherries.
Both robots cannot move outside of the grid at any moment.
Both robots should reach the bottom row in grid.
 
Example 1:
Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.
Example 2:
Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.
 
Constraints:
rows == grid.length
cols == grid[i].length
2 <= rows, cols <= 70
0 <= grid[i][j] <= 100
*/

Approach 1 - Recursion
class Solution {
    int cherryPickup(vector<vector<int>>& grid, int i, int j1, int j2){
        if(j1 < 0 || j1 >= grid[0].size() || j2 < 0 || j2 >= grid[0].size()) return -1e8;
        if(i == grid.size() - 1){
            if(j1 == j2) return grid[i][j1];
            else return grid[i][j1] + grid[i][j2];
        }
        vector<int> d = {-1, 0, 1};
        int maximum = 0;
        for(int a : d){
            for(int b : d){
                maximum = max(maximum, cherryPickup(grid, i + 1, j1 + a, j2 + b));
            }
        }
        maximum += grid[i][j1];
        if(j1 != j2) maximum += grid[i][j2];
        return maximum;
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        return cherryPickup(grid, 0, 0, grid[0].size() - 1);
    }
};
TC - O(3^n * 3^n)(Bob and alice both have 3 options each), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int cherryPickup(vector<vector<int>>& grid, int i, int j1, int j2, vector<vector<vector<int>>>& dp){
        if(j1 < 0 || j1 >= grid[0].size() || j2 < 0 || j2 >= grid[0].size()) return -1e8;
        if(i == grid.size() - 1){
            if(j1 == j2) return grid[i][j1];
            else return grid[i][j1] + grid[i][j2];
        }
        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
        vector<int> d = {-1, 0, 1};
        int maximum = 0;
        for(int a : d){
            for(int b : d){
                maximum = max(maximum, cherryPickup(grid, i + 1, j1 + a, j2 + b, dp));
            }
        }
        maximum += grid[i][j1];
        if(j1 != j2) maximum += grid[i][j2];
        return dp[i][j1][j2] = maximum;
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // dp[n][m][m], initialized to -1
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return cherryPickup(grid, 0, 0, grid[0].size() - 1, dp);
    }
};
TC - O(n * m * m) * 9(for every state, a loop of total 9 iterations is running, mentioning 9 is important because 9 is almost 10 and that means adding an extra zero)
SC - O(n * m * m + n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m)));

        for(int j1 = 0; j1 < m; j1++){
            for(int j2 = 0; j2 < m; j2++){
                dp[n - 1][j1][j2] = grid[n - 1][j1];
                if(j1 != j2) dp[n - 1][j1][j2] += grid[n - 1][j2];
            }
        }

        for(int i = n - 2; i >= 0; i--){
            for(int j1 = 0; j1 < m; j1 ++){
                for(int j2 = 0; j2 < m; j2++){
                    vector<int> d = {-1, 0, 1};
                    int maximum = -1e8;
                    for(int a : d){
                        for(int b : d){
                            int val = -1e8;
                            if(j1 + a >= 0 && j1 + a < m && j2 + b >= 0 && j2 + b < m) val = dp[i + 1][j1 + a][j2 + b];
                            maximum = max(maximum, val);
                        }
                    }
                    maximum += grid[i][j1];
                    if(j1 != j2) maximum += grid[i][j2];
                    dp[i][j1][j2] = maximum;
                }
            }
        }

        return dp[0][0][m - 1];
    }
};
TC - O(n * m * m) * 9
SC - O(n * m * m)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach - 4 can be space optimised to 2-d array of m * m, because for first dimension only i + 1 is used. so that can be omitted.