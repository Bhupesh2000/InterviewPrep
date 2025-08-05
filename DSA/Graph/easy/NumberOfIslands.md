/*
Assignment 11 Q2
https://leetcode.com/problems/number-of-islands/description/

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/

class Solution {
    void numIslandsHelper(int i, int j, int n, int m, vector<vector<char>>& grid, vector<vector<bool>>& visited){
        if(i < 0 || j < 0) return;
        if(i >= n || j >= m) return;
        if(grid[i][j] == '0') return;
        if(visited[i][j]) return;
        visited[i][j] = true;

        numIslandsHelper(i - 1, j, n, m, grid, visited);
        numIslandsHelper(i, j - 1, n, m, grid, visited);
        numIslandsHelper(i + 1, j, n, m, grid, visited);
        numIslandsHelper(i, j + 1, n, m, grid, visited);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int numIslands = 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!visited[i][j] && grid[i][j] == '1'){
                    numIslands ++;
                    numIslandsHelper(i, j, n, m, grid, visited);
                }
            }
        }

        return numIslands;
    }
};

TC - O(m * n), SC - O(max(m, n))

Can be solved via BFS as well