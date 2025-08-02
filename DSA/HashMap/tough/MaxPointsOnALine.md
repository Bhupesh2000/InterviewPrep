/*
Assignment 10 Q19
https://leetcode.com/problems/max-points-on-a-line/

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
Example 1:
Input: points = [[1,1],[2,2],[3,3]]
Output: 3

Example 2:
Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4

Constraints:
1 <= points.length <= 300
points[i].length == 2
-10^4 <= xi, yi <= 10^4
All the points are unique.
*/

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n <= 2) return n;
        int ans = 0;
        for(int i = 0; i < n; i++){
            unordered_map<double, int> slopsFreq;
            for(int j = i + 1; j < n; j++){
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                string str;
                if(x == 0){
                    slopsFreq[10001]++;
                }
                else{
                    double slop = (double)y / (double)x;
                    slopsFreq[slop]++;
                }
            }
            int temp = 0;
            for(auto x : slopsFreq){
                temp = max(temp, x.second);
            }
            ans = max(ans, temp + 1);
        }
        return ans;
    }
};

TC - O(n^2), SC - O(n)