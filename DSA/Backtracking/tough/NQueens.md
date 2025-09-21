/*
Assignment 4 Q21
https://leetcode.com/problems/n-queens/description/

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above
Example 2:
Input: n = 1
Output: [["Q"]]
 
Constraints:
1 <= n <= 9
*/

Approach 1-
class Solution {
    bool isSafeToPlace(int row, int col, int n, vector<string>& board) {
        // Check column above
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q') return false;
        }

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') return false;
        }

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') return false;
        }

        return true;
    }

    void solveNQueens(int row, vector<string>& board, int n, vector<vector<string>>& ans){
        if(row == n){
            ans.push_back(board);
            return;
        }
        for(int col = 0; col < n; col ++){
            if(isSafeToPlace(row, col, n, board)){
                board[row][col] = 'Q';
                solveNQueens(row + 1, board, n, ans);
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for(int i = 0; i < n; i++){
            board[i] = s;
        }
        solveNQueens(0, board, n, ans);
        return ans;
    }
};

Backtracking search:
At each row, you try up to n columns → branching factor ~ n.
Depth of recursion = n (one queen per row).
Worst-case search space ≈ n!.
Each placement calls isSafeToPlace, which scans up to O(n) cells (column + two diagonals).
→ Search cost = O(n · n!).
Output cost:
Every time a full solution is found, you copy the board (n × n characters).
Number of solutions for board size n = S(n).
→ Output cost = O(S(n) · n²).
Tc- O(n · n!) + O(S(n) · n²)

Recursion depth: O(n)
Board storage (current state): O(n²)
Result storage: each solution is an n × n board → O(S(n) · n²)
Auxiliary Space (excluding results): O(n²)
Total Space (including results): O(S(n) · n²)


Approach 2-
class Solution {
    // Recursive helper function
    void solveNQueens(int col,
                      vector<string>& board,   // current board configuration
                      int n,
                      vector<vector<string>>& ans, // all solutions
                      vector<int>& leftRow,        // row safety check
                      vector<int>& upperDiagonal,  // "/" diagonal safety check
                      vector<int>& lowerDiagonal)  // "\" diagonal safety check
    {
        // Base case: placed queens in all columns
        if (col == n) {
            ans.push_back(board);
            return;
        }

        // Try placing a queen in each row of the current column
        for (int row = 0; row < n; row++) {
            // Safety check: 
            // 1. leftRow[row] → is this row free?
            // 2. lowerDiagonal[row+col] → is "\" diagonal free?
            // 3. upperDiagonal[n-1 + col-row] → is "/" diagonal free?
            if (leftRow[row] == 0 &&
                lowerDiagonal[row + col] == 0 &&
                upperDiagonal[n - 1 + col - row] == 0)
            {
                // Place queen
                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;

                // Recurse for next column
                solveNQueens(col + 1, board, n, ans, leftRow, upperDiagonal, lowerDiagonal);

                // Backtrack → remove queen
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;

        // Build empty board: n strings each with n dots (.)
        vector<string> board(n, string(n, '.'));

        // Helper arrays for O(1) safety checks
        vector<int> leftRow(n, 0);          // marks rows
        vector<int> upperDiagonal(2*n - 1, 0); // "/" diagonals
        vector<int> lowerDiagonal(2*n - 1, 0); // "\" diagonals

        // Start recursion from column 0
        solveNQueens(0, board, n, ans,
                     leftRow, upperDiagonal, lowerDiagonal);

        return ans;
    }
};

🔹 How the helper arrays work
leftRow[row]
Marks whether a queen is already placed in this row.
Size = n.
Example: leftRow[2] = 1 means row 2 is blocked.
lowerDiagonal[row + col] (for \ diagonals)
All cells with same row + col lie on the same "" diagonal.
Range of row+col = 0 … 2n-2.
Size = 2n - 1.
Example on 4×4 board:
Cell (0,0) → diag = 0
Cell (1,1) → diag = 2
Cell (3,1) → diag = 4
upperDiagonal[n-1 + col - row] (for / diagonals)
All cells with same (col - row) lie on the same "/" diagonal.
To keep index positive, we shift by (n-1).
Range of col-row = -(n-1)…(n-1) → after shift = 0…2n-2.
Size = 2n - 1.
Example on 4×4 board:
Cell (0,3) → index = 3 - 0 + (3) = 6
Cell (1,2) → index = 2 - 1 + (3) = 4
Cell (3,0) → index = 0 - 3 + (3) = 0

🔹 Why use these arrays?
Naive check for each queen would take O(n) per step (scan rows + diagonals).
With these arrays, we reduce checks to O(1).
So the recursion tree remains O(n!) solutions explored, but each placement check is constant.

Time: O(n!) (all possible queen placements explored with pruning).
Space: O(n²) for the board + O(n) for rows + O(2n-1) + O(2n-1) ≈ O(n²).