/*
Assignment 11 Q13
https://leetcode.com/problems/course-schedule-ii/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.
For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]
 
Constraints:
1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.
*/

class Solution {
    vector<vector<int>> createAdjList(int numCourses, vector<vector<int>>& prerequisites){
        vector<vector<int>> adj(numCourses);
        for(int i = 0; i < prerequisites.size(); i++){
            int s1 = prerequisites[i][0];
            int s2 = prerequisites[i][1];
            adj[s1].push_back(s2);
        }
        return adj;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj = createAdjList(numCourses, prerequisites);
        vector<int> indegree(numCourses, 0);
        vector<int> ans(numCourses);
        for(int i = 0; i < numCourses; i++){
            for(int j = 0; j < adj[i].size(); j++){
                indegree[adj[i][j]] ++;
            }
        }

        queue<int> q;
        int count = 0;

        for(int i = 0; i < numCourses; i++)
            if(indegree[i] == 0) q.push(i);

        while(!q.empty()){
            int front = q.front();
            q.pop();
            count ++;
            ans[numCourses - count] = front;
            for(int i = 0; i < adj[front].size(); i++){
                int index = adj[front][i];
                indegree[index] --;
                if(indegree[index] == 0) q.push(index);
            }
        }

        return (count == numCourses) ? ans : vector<int>();
    }
};