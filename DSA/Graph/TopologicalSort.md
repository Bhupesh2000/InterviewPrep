Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge u -> v, vertex u comes before v in the ordering.

Input: V = 4, E = 3, edges[][] = [[3, 0], [1, 0], [2, 0]]
Few valid Topological orders for the given graph are:
[3, 2, 1, 0]
[1, 2, 3, 0]
[2, 3, 1, 0]

Approach 1 - Topological Sorting DFS
class Solution {
    void createAdj(vector<vector<int>>& edges, vector<vector<int>>& adj){
        for(auto it : edges){
            adj[it[0]].push_back(it[1]);
        }
    }
    
    void dfs(int node, vector<vector<int>>& adj, stack<int>& topoList, vector<bool>& visited){
        visited[node] = 1;
        for(auto i : adj[node]){
             if (!visited[i]) dfs(i, adj, topoList, visited);
        }
        topoList.push(node);
    }
    
  public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        // code here
        vector<vector<int>> adj(V);
        createAdj(edges, adj);
        stack<int> topoList;
        vector<bool> visited(V, false);
        for(int i = 0; i < V; i++){
            if(!visited[i]) dfs(i, adj, topoList, visited);
        }
        vector<int> ans;
        while(!topoList.empty()){
            ans.push_back(topoList.top());
            topoList.pop();
        }
        return ans;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Topological Sort BFS(Kahn's Algorithm)
Will use the concept of Indegree (no. of incoming edges to a node)
#include <bits/stdc++.h>
void createAdj(vector<vector<int>> &edges, vector<vector<int>> &adj, vector<int> &inorder){
    for(auto i : edges){
        adj[i[0]].push_back(i[1]);
        inorder[i[1]] ++;
    }
}
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
    vector<vector<int>> adj(v);
    vector<int> inorder(v, 0);
    createAdj(edges, adj, inorder);
    queue<int> q;
    for(int i = 0; i < v; i++){
        if(inorder[i] == 0) q.push(i);
    }
    vector<int> ans;
    while(!q.empty()){
        int node = q.front();
        ans.push_back(node);
        q.pop();
        for(auto i : adj[node]){
            inorder[i] --;
            if(inorder[i] == 0) q.push(i);
        }
    }
    return ans;
}