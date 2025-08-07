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

Approach 2 - using ordered set
class Solution {
    void createAdjList(vector<vector<int>> &edges, vector<vector<pair<int, int>>>& adj){
        for(int i = 0; i < edges.size(); i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        }
    }
  public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        vector<vector<pair<int, int>>> adj(V);
        createAdjList(edges, adj);

        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        set<pair<int, int>> st;
        st.insert({0, src});
        
        while(!st.empty()){
            pair<int, int> top = *st.begin(); 
            st.erase(st.begin());
            int d = top.first, node = top.second;
            for(auto it : adj[node]){
                int n1 = it.first, d1 = it.second;
                if(dist[n1] > d + d1){
                    if(dist[n1] != INT_MAX){
                        st.erase({dist[n1], n1});
                    }
                    dist[n1] = d + d1;
                    st.insert({d + d1, n1});
                }
            }
        }

        return dist;
    }
};
TC - O(ElogV)

The benefit of using set is that we can erase the pairs which has more distance, so saving some iterations.
But this will be a minor benefit, because erase will be logrithmic operation and thus there is a possibility that we might end up taking more time than priority queue. So it depends upon case to case.