/*
https://leetcode.com/problems/triangle/description/

Given a triangle array, return the minimum path sum from top to bottom.
For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
Example 2:
Input: triangle = [[-10]]
Output: -10
 
Constraints:
1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-10^4 <= triangle[i][j] <= 10^4

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
*/

Approach 1 - Recursion
class Solution {
    int minimumTotal(vector<vector<int>>& triangle,  int i, int j, int currSum){
        currSum += triangle[i][j];
        if(i == triangle.size() - 1) return currSum;
        int a = minimumTotal(triangle, i + 1, j, currSum);
        int b = minimumTotal(triangle, i + 1, j + 1, currSum);
        return min(a, b);
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        return minimumTotal(triangle, 0, 0, 0);
    }
};
Tc - no. of blocks = 1 + 2 + ... + n and each col has 2 calls - 2 ^(1 + 2 + ... n) => O(2 ^(n^2))
Sc - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int minimumTotal(vector<vector<int>>& triangle,  int i, int j, vector<vector<int>>& dp){
        if(i == triangle.size() - 1) return triangle[i][j];
        if(dp[i][j] != INT_MIN) return dp[i][j];
        int a = minimumTotal(triangle, i + 1, j, dp);
        int b = minimumTotal(triangle, i + 1, j + 1, dp);
        return dp[i][j] = min(a, b) + triangle[i][j];
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        return minimumTotal(triangle, 0, 0, dp);
    }
};
TC - O(n^2), SC - O(n^2) + O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - Tabulation
class Solution {
    int minimumTotal(vector<vector<int>>& triangle,  int i, int j, vector<vector<int>>& dp){
        if(i == triangle.size() - 1) return triangle[i][j];
        if(dp[i][j] != INT_MIN) return dp[i][j];
        int a = minimumTotal(triangle, i + 1, j, dp);
        int b = minimumTotal(triangle, i + 1, j + 1, dp);
        return dp[i][j] = min(a, b) + triangle[i][j];
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n));
        dp[0][0] = triangle[0][0];
        for(int i = 1; i < n; i++){
            dp[i][0] = dp[i - 1][0] + triangle[i][0];
            for(int j = 1; j < i; j ++){
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
            }
            dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
        }
        int minimum = dp[n - 1][0];
        for(int i = 1; i < n; i++){
            minimum = min(minimum, dp[n - 1][i]);
        }
        return minimum;
    }
};
TC - O(n^2), SC - O(n^2)
**** try filling the array from bottom to top
dp[i][j] = min(dp[i + 1][j], dp[i + 1][j]) + triangle[i][j];
the value at 0,0 will be the ans

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - dp with space optmisation
TC - O(n^2), SC - O(N)