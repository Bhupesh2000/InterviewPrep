/*
Assignment 11 Q15
https://leetcode.com/problems/the-time-when-the-network-becomes-idle

*/

class Solution {
    void createAdjList(vector<vector<int>> &edges, vector<vector<int>> &adj){
        for(auto &e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    void Djikstras(vector<vector<int>> &adj, vector<int> &dist){
        dist[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});
        while(!pq.empty()){
            auto [d, node] = pq.top();
            pq.pop();

            if(d > dist[node]) continue;

            for(auto neighbor : adj[node]){
                if(dist[neighbor] > dist[node] + 1){
                    dist[neighbor] = dist[node] + 1;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
    }

    void bfs(vector<vector<int>>& adj, vector<int>& dist) {
        queue<int> q;
        dist[0] = 0;
        q.push(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adj[node]) {
                if (dist[neighbor] == INT_MAX) { // unvisited
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        int n = patience.size();
        vector<vector<int>> adj(n);
        vector<int> dist(n, INT_MAX);
        createAdjList(edges, adj);
        bfs(adj, dist);
        int maxTime = 0;
        for(int i = 1; i < n; i++){
            int roundTrip = 2 * dist[i];
            int lastReplyTime;
            if(roundTrip <= patience[i]){
                lastReplyTime = roundTrip;
            } else {
                int lastSentTime = ((roundTrip - 1) / patience[i]) * patience[i];
                lastReplyTime = lastSentTime + roundTrip;
            }
            maxTime = max(maxTime, lastReplyTime);
        }
        return maxTime + 1;
    }
};

Aprroach 1 - using Djikstras to get dist vector
Time Complexity:
Using a binary heap: O((V + E) log V)
Each vertex is inserted into the priority queue once
Each edge causes at most one push
Space Complexity:
O(V + E) for adjacency list
O(V) for dist array and priority queue
Overall:
TC: O((V + E) log V)
SC: O(V + E)

Approach 2 - using BFS(since all edge weights are 1)
Time Complexity:
O(V + E)
V = number of vertices (nodes)
E = number of edges
Each node is visited once, each edge is processed twice (undirected).
Space Complexity:
O(V + E) for adjacency list
O(V) for dist array and BFS queue
Overall:
TC: O(V + E)
SC: O(V + E)
