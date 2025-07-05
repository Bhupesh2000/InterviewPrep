/*
Assignment 6 Q17
https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign

Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example 1:
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1
 
Constraints:
rows == matrix.length
cols == matrix[i].length
1 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
*/

class Solution {
    int findMaxHistArea(vector<vector<int>>& heightsMatrix, int row){
        int n = heightsMatrix[0].size();
        stack<int> st;
        int maxArea = 0;
        for(int i = 0; i < n; i++){
            while(!st.empty() && heightsMatrix[row][i] < heightsMatrix[row][st.top()]){
                int topElementIndex = st.top();
                st.pop();
                int leftIndex = i;
                int prevIndex = (st.empty()) ? -1 : st.top();
                maxArea = max(maxArea, (leftIndex - prevIndex - 1) * (heightsMatrix[row][topElementIndex]));
            }
            st.push(i);
        }
        while(!st.empty()){
            int topElementIndex = st.top();
            st.pop();
            int leftIndex = n;
            int prevIndex = (st.empty()) ? -1 : st.top();
            maxArea = max(maxArea, (leftIndex - prevIndex - 1) * (heightsMatrix[row][topElementIndex]));
        }
        return maxArea;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> heightsMatrix(m, vector<int> (n, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                heightsMatrix[j][i] = matrix[j][i] - '0';
                if(heightsMatrix[j][i] == 1 && j > 0) heightsMatrix[j][i] += heightsMatrix[j - 1][i];
            }
        }

        int maxArea = 0;
        for(int i = 0; i < m; i++){
            maxArea = max(maxArea, findMaxHistArea(heightsMatrix, i));
        }

        return maxArea;
    }
};

✅ Time and Space Complexity
Time: O(m * n)
    Histogram build: O(m * n)
    Histogram processing per row: O(n) × m rows
Space: O(n) for stack + O(m * n) for heightsMatrix