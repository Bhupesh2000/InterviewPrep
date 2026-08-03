/*
Assignment 11 Q6
https://practice.geeksforgeeks.org/problems/shortest-source-to-destination-path/0

Given a 2D binary matrix A(0-based index) of dimensions NxM. Find the minimum number of steps required to reach from (0,0) to (X, Y).
Note: You can only move left, right, up and down, and only through cells that contain 1.

Example 1:
Input:
N=3, M=4
A=[[1,0,0,0], 
   [1,1,0,1],
   [0,1,1,1]]
X=2, Y=3 
Output:
5
Explanation:
The shortest path is as follows:
(0,0)->(1,0)->(1,1)->(2,1)->(2,2)->(2,3).

Example 2:
Input:
N=3, M=4
A=[[1,1,1,1],
   [0,0,0,1],
   [0,0,0,1]]
X=0, Y=3
Output:
3
Explanation:
The shortest path is as follows:
(0,0)->(0,1)->(0,2)->(0,3).

Your Task:
You don't need to read input or print anything. Your task is to complete the function shortestDistance() which takes the integer N, M, X, Y, and the 2D binary matrix A as input parameters and returns the minimum number of steps required to go from (0,0) to (X, Y).If it is impossible to go from (0,0) to (X, Y),then function returns -1. If value of the cell (0,0) is 0 (i.e  A[0][0]=0) then return -1.

Constraints:
1 <= N,M <= 250
0 <= X < N
0 <= Y < M
0 <= A[i][j] <= 1
*/

// User function Template for C++
typedef pair<pair<int, int>, int> pii;
class Solution {
  public:
    int shortestDistance(int N, int M, vector<vector<int>> A, int X, int Y) {
        if(A[0][0] == 0) return -1;
        int n = A.size(), m = A[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pii> q;
        int minDis = INT_MAX;
        q.push({{0,0}, 0});
        visited[0][0] = true;
        while(!q.empty()){
            pii front = q.front();
            q.pop();
            pair<int, int> coords = front.first;
            int i = coords.first, j = coords.second;
            int dist = front.second;
            if(i == X && j == Y) minDis = min(dist, minDis);
            else{
                if(i > 0 && A[i - 1][j] == 1 && !visited[i - 1][j]){
                    q.push({{i - 1, j}, dist + 1});
                    visited[i - 1][j] = true;
                }
                if(j > 0 && A[i][j - 1] == 1 && !visited[i][j - 1]){
                    q.push({{i, j - 1}, dist + 1});
                    visited[i][j - 1] = true;
                }
                if(i < N - 1 && A[i + 1][j] == 1 && !visited[i + 1][j]){
                    q.push({{i + 1, j}, dist + 1});
                    visited[i + 1][j] = true;
                }
                if(j < M - 1 && A[i][j + 1] == 1 && !visited[i][j + 1]){
                    q.push({{i, j + 1}, dist + 1});
                    visited[i][j + 1] = true;
                }
            }
        }
        return (minDis == INT_MAX) ? -1 : minDis;
    }
};