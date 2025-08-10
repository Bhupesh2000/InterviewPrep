/*
https://leetcode.com/problems/course-schedule-ii/description/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 
Constraints:
1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
*/

class Solution {
    vector<vector<int>> createAdjList(int n, vector<vector<int>>& prerequisites){
        vector<vector<int>> adj(n);
        for(int i = 0; i < prerequisites.size(); i++){
            int s1 = prerequisites[i][0];
            int s2 = prerequisites[i][1];
            adj[s1].push_back(s2);
        }
        return adj;
    }

bool isCyclePresentBFS(int n, vector<vector<int>>& adj){
    vector<int> indegree(n, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            indegree[adj[i][j]] ++;
        }
    }

    queue<int> q;
    int count = 0;

    for(int i = 0; i < n; i++)
        if(indegree[i] == 0) q.push(i);

    while(!q.empty()){
        int front = q.front();
        q.pop();
        count ++;
        for(int i = 0; i < adj[front].size(); i++){
            int index = adj[front][i];
            indegree[index] --;
            if(indegree[index] == 0) q.push(index);
        }
    }

    return count != n;
}

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj = createAdjList(numCourses, prerequisites);

        if(isCyclePresentBFS(numCourses, adj)) return false;
        return true;
    }
};