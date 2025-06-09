/*
Given a n * n 2D matrix, the task to find the sum of all the submatrices.

Examples: 

Input :  mat[][] = [[1, 1],
                         [1, 1]];
Output : 16
Explanation: 
Number of sub-matrices with 1 elements = 4
Number of sub-matrices with 2 elements = 4
Number of sub-matrices with 3 elements = 0
Number of sub-matrices with 4 elements = 1

Since all the entries are 1, the sum becomes
sum = 1 * 4 + 2 * 4 + 3 * 0 + 4 * 1 = 16

Input : mat[][] = [[1, 2, 3],
                         [4, 5, 6],
                        [7, 8, 9]]
Output : 500
*/

#include <iostream>
#include <vector>
using namespace std;

// Function to find the sum of all submatrices 
int matrixSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int res = 0;
    
    // Iterate through each element in the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            // Number of ways to choose the top-left corner 
            int topLeft = (i + 1) * (j + 1);
            
            // Number of ways to choose the bottom-right corner
            int bottomRight = (n - i) * (n - j);
            
            // Calculate contribution of current element
            res += (topLeft * bottomRight * matrix[i][j]);
        }
    }
    
    return res;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 1},
        {1, 1}
    };
    
    cout << matrixSum(matrix);
    return 0;
}