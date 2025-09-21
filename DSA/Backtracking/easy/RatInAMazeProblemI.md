/*
https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1

Consider a rat placed at position (0, 0) in an n x n square matrix mat[][]. The rat's goal is to reach the destination at position (n-1, n-1). The rat can move in four possible directions: 'U'(up), 'D'(down), 'L' (left), 'R' (right).
The matrix contains only two possible values:
0: A blocked cell through which the rat cannot travel.
1: A free cell that the rat can pass through.
Your task is to find all possible paths the rat can take to reach the destination, starting from (0, 0) and ending at (n-1, n-1), under the condition that the rat cannot revisit any cell along the same path. Furthermore, the rat can only move to adjacent cells that are within the bounds of the matrix and not blocked.
If no path exists, return an empty list.
Note: Return the final result vector in lexicographically smallest order.

Examples:
Input: mat[][] = [[1, 0, 0, 0], [1, 1, 0, 1], [1, 1, 0, 0], [0, 1, 1, 1]]
Output: ["DDRDRR", "DRDDRR"]
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.
Input: mat[][] = [[1, 0], [1, 0]]
Output: []
Explanation: No path exists as the destination cell is blocked.
Input: mat = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
Output: ["DDRR", "RRDD"]
Explanation: The rat has two possible paths to reach the destination: 1. "DDRR" 2. "RRDD", These are returned in lexicographically sorted order.
Constraints:
2 ≤ mat.size() ≤ 5
0 ≤ mat[i][j] ≤ 1
*/

class Solution {
    void ratInMaze(int row, int col, string& s, vector<vector<int>>& maze, vector<string>& ans){
        int n = maze.size();
        if(row == n - 1 && col == n - 1){
            ans.push_back(s);
            return;
        }
        
        maze[row][col] = 0;
        if(row < n - 1 && maze[row + 1][col] == 1){
            s += 'D';
            ratInMaze(row + 1, col, s, maze, ans);
            s.pop_back();
        }
        if(col >= 1 && maze[row][col - 1] == 1){
            s += 'L';
            ratInMaze(row, col - 1, s, maze, ans);
            s.pop_back();
        }
        if(col < n - 1 && maze[row][col + 1] == 1){
            s += 'R';
            ratInMaze(row, col + 1, s, maze, ans);
            s.pop_back();
        }
        if(row >= 1 && maze[row - 1][col] == 1){
            s += 'U';
            ratInMaze(row - 1, col, s, maze, ans);
            s.pop_back();
        }
        maze[row][col] = 1;
    }
  public:
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        // code here
        vector<string> ans;
        string s;
        ratInMaze(0, 0, s, maze, ans);
        return ans;
    }
};