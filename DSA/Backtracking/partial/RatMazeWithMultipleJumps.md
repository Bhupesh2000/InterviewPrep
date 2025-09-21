/*
Assignment-4 Q19
https://www.geeksforgeeks.org/problems/rat-maze-with-multiple-jumps3852/1

A maze is given as n*n matrix of blocks where source block is the upper left most block i.e., matrix[0][0] and destination block is lower rightmost block i.e., matrix[n-1][n-1]. A rat starts from source and has to reach the destination.
The rat can move in only two directions: first forward (if possible) or down.
In the maze matrix, 0 means the block is the dead end and non-zero number means the block can be used in the path from source to destination. The non-zero value of mat[i][j] indicates number of maximum jumps rat can make from cell mat[i][j]. 
Return a maxtrix of size n*n in which 1 at (i, j) represents the cell is taken into the path otherwise 0 .
Note : If multiple solutions exist, the shortest earliest hop will be accepted. For the same hop distance at any point, forward will be preferred over downward. 

Example:
Input: {{2,1,0,0},{3,0,0,1},{0,1,0,1},
{0,0,0,1}}
Output: {{1,0,0,0},{1,0,0,1},{0,0,0,1},
{0,0,0,1}}
Explanation: Rat started with matrix[0][0] and 
can jump up to 2 steps right/down. First check 
matrix[0][1] as it is 1, next check 
matrix[0][2] ,this won't lead to the solution. 
Then check matrix[1][0], as this is 3(non-zero)
,so we can make 3 jumps to reach matrix[1][3]. 
From matrix[1][3] we can move downwards taking 
1 jump each time to reach destination at 
matrix[3][3].
Example 2:
Input: {{2,1,0,0},{2,0,0,1},{0,1,0,1},
{0,0,0,1}}
Output: {{-1}}
Explanation: As no path exists so, -1.
 
Your Task:
You don't need to read or print anyhting, Your task is to complete the function ShortestDistance() which takes the matrix as input parameter and returns a matrix of size n if path exists otherwise returns a matrix of 1x1 which contains -1. In output matrix, 1 at (i, j) represents the cell is taken into the path otherwise 0 if any path exists.
 
Expected Time Complexity: O(n*n*k) where k is max(matrix[i][j])
Expected Space Complexity: O(1)
 

Constraints:
1 <= n <= 50
1 <= matrix[i][j] <= 20
*/

class Solution {
    bool ShortestDistance(vector<vector<int>>& matrix, int r, int c, int n, vector<vector<int>>& ans){
        if(r == n - 1 && c == n - 1) return true;
        int a = matrix[r][c];
        for(int i = 1; i <= a; i++){
            if(c + i < n){
                ans[r][c + i] = 1;
                if(ShortestDistance(matrix, r, c + i, n, ans)) return true;
                ans[r][c + i] = 0;
            }
            if(r + i < n){
                ans[r + i][c] = 1;
                if(ShortestDistance(matrix, r + i, c, n, ans)) return true;
                ans[r + i][c] = 0;
            }
        }
        return false;
    }
  public:
    vector<vector<int>> ShortestDistance(vector<vector<int>>& matrix) {
        // Code here
        int n = matrix.size();
        vector<vector<int>> ans(n, vector<int>(n, 0));
        if(matrix[0][0] == 0 && n != 1) return vector<vector<int>>(1, vector<int>(1, -1));
        ans[0][0] = 1;
        ShortestDistance(matrix, 0, 0, n, ans);
        return ans;
    }
};