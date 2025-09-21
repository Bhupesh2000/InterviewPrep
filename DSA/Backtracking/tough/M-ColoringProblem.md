/*
https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1

You are given an undirected graph consisting of V vertices and E edges represented by a list edges[][], along with an integer m. Your task is to determine whether it is possible to color the graph using at most m different colors such that no two adjacent vertices share the same color. Return true if the graph can be colored with at most m colors, otherwise return false.
Note: The graph is indexed with 0-based indexing.

Examples:
Input: V = 4, edges[][] = [[0, 1], [1, 3], [2, 3], [3, 0], [0, 2]], m = 3
Output: true
Explanation: It is possible to color the given graph using 3 colors, for example, one of the possible ways vertices can be colored as follows:
Vertex 0: Color 1
Vertex 1: Color 2
Vertex 2: Color 2
Vertex 3: Color 3
Input: V = 3, edges[][] = [[0, 1], [1, 2], [0, 2]], m = 2
Output: false
Explanation: It is not possible to color the given graph using only 2 colors because vertices 0, 1, and 2 form a triangle.
Constraints:
1 ≤ V ≤ 10
1 ≤ E = edges.size() ≤ (V*(V-1))/2
0 ≤ edges[i][j] ≤ V-1
1 ≤ m ≤ V
*/

class Solution {
    void createAdjList(vector<vector<int>> &edges, vector<vector<int>> &adjList){
        for(int i = 0; i < edges.size(); i++){
            vector<int> v = edges[i];
            int n1 = v[0], n2 = v[1];
            adjList[n1].push_back(n2);
            adjList[n2].push_back(n1);
        }
    }
    bool isColorPossible(vector<vector<int>> &adjList, int node, int i, vector<int> &color){
        for(int n : adjList[node]){
            if(color[n] == i) return false;
        }
        return true;
    }
    bool solve(vector<vector<int>> &adjList, int idx, vector<int> &color, int m){
        if(idx == adjList.size()) return true;
        if(color[idx] != 0) return solve(adjList, idx + 1, color, m);
        for(int c = 1; c <= m; c ++){
            if(!isColorPossible(adjList, idx, c, color)) continue;
            color[idx] = c;
            if(solve(adjList, idx + 1, color, m)) return true;
            color[idx] = 0;
        }
        return false;
    }
  public:
    bool graphColoring(int v, vector<vector<int>> &edges, int m) {
        vector<vector<int>> adjList(v);
        createAdjList(edges, adjList);
        vector<int> color(v, 0);
        return solve(adjList, 0, color, m);
    }
};

TC - O(m^V * (V+E))
SC - O(V + E)(adjList) + O(V)(color) + O(V)(recursion stack) = O(V + E)