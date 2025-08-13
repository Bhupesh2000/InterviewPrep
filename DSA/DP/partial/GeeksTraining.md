/*
https://www.geeksforgeeks.org/problems/geeks-training/1

Geek is going for a training program for n days. He can perform any of these activities: Running, Fighting, and Learning Practice. Each activity has some point on each day. As Geek wants to improve all his skills, he can't do the same activity on two consecutive days. Given a 2D array arr[][] of size n where arr[i][0], arr[i][1], and arr[i][2] represent the merit points for Running, Fighting, and Learning on the i-th day, determine the maximum total merit points Geek can achieve .

Example:
Input: arr[]= [[1, 2, 5], [3, 1, 1], [3, 3, 3]]
Output: 11
Explanation: Geek will learn a new move and earn 5 point then on second day he will do running and earn 3 point and on third day he will do fighting and earn 3 points so, maximum merit point will be 11.
Input: arr[]= [[1, 1, 1], [2, 2, 2], [3, 3, 3]]
Output: 6
Explanation: Geek can perform any activity each day while adhering to the constraints, in order to maximize his total merit points as 6.
Input: arr[]= [[4, 2, 6]]
Output: 6
Explanation: Geek will learn a new move to make his merit points as 6.
Constraint:
1 <=  n <= 10^5   
1 <=  arr[i][j] <= 100
*/

Approach 1 - Recursion
class Solution {
    int maximumPoints(int ind, vector<vector<int>>& arr, int last){
        if(ind == 0){
            int points = 0;
            for(int i = 0; i < 3; i++){
                if(i == last) continue;
                points = max(points, arr[0][i]);
            }
            return points;
        }
        int maxPoints = 0;
        for(int i = 0; i < 3; i++){
            if(i == last) continue;
            maxPoints = max(maxPoints, maximumPoints(ind - 1, arr, i) + arr[ind][i]);
        }
        return maxPoints;
    }
  public:
    int maximumPoints(vector<vector<int>>& arr) {
        return maximumPoints(arr.size() - 1, arr, 3);
    }
};
TC - O(2^n) -> 2 because 1 exercise is eliminated from each day. Hence call upon only 2, SC - O(n), n is the no. of days

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Memoization
class Solution {
    int maximumPoints(int ind, vector<vector<int>>& arr, int last, vector<vector<int>>& dp){
        if(ind == 0){
            int points = 0;
            for(int i = 0; i < 3; i++){
                if(i == last) continue;
                points = max(points, arr[0][i]);
            }
            return points;
        }
        if(dp[ind][last] != -1) return dp[ind][last];
        int maxPoints = 0;
        for(int i = 0; i < 3; i++){
            if(i == last) continue;
            maxPoints = max(maxPoints, maximumPoints(ind - 1, arr, i, dp) + arr[ind][i]);
        }
        return dp[ind][last] = maxPoints;
    }
  public:
    int maximumPoints(vector<vector<int>>& arr) {
        vector<vector<int>> dp(arr.size(), vector<int>(4, -1));
        return maximumPoints(arr.size() - 1, arr, 3, dp);
    }
};
TC - O(n), SC - O(2n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - DP
class Solution {
  public:
    int maximumPoints(vector<vector<int>>& arr) {
        int n = arr.size();
        if(n == 0) return 0;
        if(n == 1){
            int points = 0;
            for(int i = 0; i < 3; i++){
                points = max(points, arr[0][i]);
            }
            return points;
        }
        vector<vector<int>> dp(n, vector<int>(3, 0));
        for(int i = 0; i < 3; i++){ dp[0][i] = arr[0][i]; }
        
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 3; j++){
                int points = 0;
                for(int k = 0; k < 3; k ++){
                    if(k == j) continue;
                    points = max(points, dp[i - 1][k]);
                }
                dp[i][j] = points + arr[i][j];
            }
        }
        
        int maxPoints = dp[n - 1][0];
        for(int i = 1; i < 3; i++){
            maxPoints = max(maxPoints, dp[n - 1][i]);
        }
        return maxPoints;
        
    }
};
TC - O(n), Sc - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - dp with space optimisation
class Solution {
  public:
    int maximumPoints(vector<vector<int>>& arr) {
        int n = arr.size();
        if(n == 0) return 0;
        if(n == 1){
            int points = 0;
            for(int i = 0; i < 3; i++){
                points = max(points, arr[0][i]);
            }
            return points;
        }
        vector<int> prev(3);
        for(int i = 0; i < 3; i++){ prev[i] = arr[0][i]; }
        
        for(int i = 1; i < n; i++){
            vector<int> curr(3);
            for(int j = 0; j < 3; j++){
                int points = 0;
                for(int k = 0; k < 3; k ++){
                    if(k == j) continue;
                    points = max(points, prev[k]);
                }
                curr[j] = points + arr[i][j];
            }
            prev = curr;
        }
        
        int maxPoints = prev[0];
        for(int i = 1; i < 3; i++){
            maxPoints = max(maxPoints, prev[i]);
        }
        return maxPoints;
        
    }
};
Tc - O(n), SC - O(1)