Dijkstra Algo - Algo to find minimum distance b/w two points of a graph. It does not work with negative weight edges graph

Approach 1 - Using min priority queue
class Solution {
    void createAdjList(vector<vector<int>> &edges, vector<vector<pair<int, int>>>& adj){
        for(int i = 0; i < edges.size(); i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        }
    }
  public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        // Code here
        vector<vector<pair<int, int>>> adj(V);
        createAdjList(edges, adj);

        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        // Min-heap: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({0, src});

        while(!q.empty()){
            pair<int, int> p = q.top();
            q.pop();

            int d = p.first, node = p.second;
            if(d > dist[node]) continue;

            for(auto pi : adj[node]){
                int neighbor = pi.first, weight = pi.second;
                if(dist[neighbor] > dist[node] + weight){
                    dist[neighbor] = dist[node] + weight;
                    q.push({dist[neighbor], neighbor});
                }
            }
        }

        return dist;
    }
};
TC - O(ElogV), E -> total no. of edges, V -> total no. of vertices