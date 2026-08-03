/*
Assignment 11 Q5
https://leetcode.com/problems/surrounded-regions/

You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.

Example 1:
Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation:
In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.

Example 2:
Input: board = [["X"]]
Output: [["X"]]

Constraints:
m == board.length
n == board[i].length
1 <= m, n <= 200
board[i][j] is 'X' or 'O'.
*/

class Solution {
    void DFS(int i, int j, int n, int m, vector<vector<char>>& board){
        board[i][j] = '-';
        if(i > 0 && board[i - 1][j] == 'O') DFS(i - 1, j, n, m, board);
        if(j > 0 && board[i][j - 1] == 'O') DFS(i, j - 1, n, m, board);
        if(i < n - 1 && board[i + 1][j] == 'O') DFS(i + 1, j, n, m, board);
        if(j < m - 1 && board[i][j + 1] == 'O') DFS(i, j + 1, n, m, board);
    }
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size(), m = board[0].size();
        if(n <= 2 || m <= 2) return;
        for(int i = 0; i < m; i++){
            if(board[0][i] == 'O') DFS(0, i, n, m, board);
        }
        for(int i = 0; i < n; i++){
            if(board[i][0] == 'O') DFS(i, 0, n, m, board);
        }
        for(int i = 0; i < m; i++){
            if(board[n - 1][i] == 'O') DFS(n - 1, i, n, m, board);
        }
        for(int i = 0; i < n; i++){
            if(board[i][m - 1] == 'O') DFS(i, m - 1, n, m, board);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == '-') board[i][j] = 'O';
            }
        }
    }
};

TC - O(n * m), SC - O(n * m) -> recursion stack(worst case when all are '0')