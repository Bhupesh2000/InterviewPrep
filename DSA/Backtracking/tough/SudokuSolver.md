/*
https://leetcode.com/problems/sudoku-solver/

Write a program to solve a Sudoku puzzle by filling the empty cells.
A sudoku solution must satisfy all of the following rules:
Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

Example 1:
Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]

Constraints:
board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'.
It is guaranteed that the input board has only one solution.
*/

class Solution {
    bool isValid(vector<vector<char>>& board, int row, int col, char k){
        for(int i = 0; i < 9; i++){
            if(board[i][col] == k) return false;
            if(board[row][i] == k) return false;
            if(board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == k) return false;
        }
        return true;
    }
    bool solve(vector<vector<char>>& board){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.'){
                    for(char k = '1'; k <= '9'; k++){
                        if(isValid(board, i, j, k)){
                            board[i][j] = k;
                            if(solve(board)) return true;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};

Time Complexity
Let E be the number of empty cells.
Each empty cell can try up to 9 digits.
For each trial, isValid does a constant-work scan of:
the row (≤ 9 checks),
the column (≤ 9 checks),
the 3×3 box (≤ 9 checks via indexed access).
So isValid = O(9) = O(1) (constant for fixed 9×9).
Worst-case search time:
O(9^E)
(Exponential in the number of empty cells; pruning makes it much faster in practice.)

Space Complexity
Recursion depth: at most E (one stack frame per filled cell), so O(E).
For a standard 9×9 Sudoku, E ≤ 81, hence this is a small constant in practice.
Board storage: modified in place → O(1) extra.
Total auxiliary space:
O(E)   (≤ O(81) for 9×9)  → effectively O(1) for fixed-size Sudoku

Summary
Time:  O(9^E)
Space: O(E) auxiliary (≤ 81 for 9×9), in-place board