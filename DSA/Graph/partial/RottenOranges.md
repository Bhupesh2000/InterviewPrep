/*
https://leetcode.com/problems/rotting-oranges/

You are given an m x n grid where each cell can have one of three values:
0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 
Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.
*/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> visited = grid; // not required. in place change can be done for the grid vector
        queue<pair<pair<int, int>, int>> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 2) 
                {
                    q.push({{i, j}, 0});
                }
            }
        }

        int time = 0;

        while(!q.empty()){
            pair<pair<int, int>, int> p = q.front();
            q.pop();
            pair<int, int> coords = p.first;
            int t = p.second;
            int i = coords.first, j = coords.second;
            if(i - 1 >= 0 && visited[i - 1][j] == 1){
                q.push({{i - 1, j}, t + 1});
                visited[i - 1][j] = 2;
            }
            if(j - 1 >= 0 && visited[i][j - 1] == 1){
                q.push({{i, j - 1}, t + 1});
                visited[i][j - 1] = 2;
            }
            if(i + 1 < m && visited[i + 1][j] == 1){
                q.push({{i + 1, j}, t + 1});
                visited[i + 1][j] = 2;
            }
            if(j + 1 < n && visited[i][j + 1] == 1){
                q.push({{i, j + 1}, t + 1});
                visited[i][j + 1] = 2;
            }
            time = max(time, t);
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(visited[i][j] == 1) return -1;
            }
        }

        return time;
    }
};

TC - O(m * n), SC - O(m * n)