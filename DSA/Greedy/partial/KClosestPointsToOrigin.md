/*
Assignment 8 Q10
https://leetcode.com/problems/k-closest-points-to-origin/

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).
You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

Example 1:
Input: points = [[1,3],[-2,2]], k = 1
Output: [[-2,2]]
Explanation:
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].

Example 2:
Input: points = [[3,3],[5,-1],[-2,4]], k = 2
Output: [[3,3],[-2,4]]
Explanation: The answer [[-2,4],[3,3]] would also be accepted.

Constraints:
1 <= k <= points.length <= 10^4
-10^4 <= xi, yi <= 10^4
*/

Approach 1 - 
Sorting the input array based on the distances using a comprator.
TC - O(NlogN) -> for sorting + k -> for storing in res
SC - O(k) -> for result

Approach 2 -
using max heap

typedef pair<long long, vector<int>> pv;
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size();
        priority_queue<pv> pq;
        for(int i = 0; i < k; i++){
            long long x = points[i][0], y = points[i][1];
            pq.push({(x * x + y * y), points[i]});
        }
        for(int i = k; i < n; i++){
            long long x = points[i][0], y = points[i][1];
            pq.push({(x * x + y * y), points[i]});
            pq.pop();
        }
        vector<vector<int>> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }
};

TC - O(Nlogk) -> for pushing in maxheap + O(k) -> for storing in maxheap
SC - O(k) -> for heap + O(k) -> for res vector