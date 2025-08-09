Spanning Tree - A tree in which we have N nodes and N - 1 edges and all nodes are reachable from each other
Minimum Spanning Tree - A spanning tree with minium edge weight sum

Prim's Algorithm - 
class Solution {
    void createAdjList(vector<vector<int>>& edges, vector<vector<pair<int, int>>>& adj){
        for(auto &e : edges){
            int u = e[0], v = e[1], wt = e[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
    }
  public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(V);
        createAdjList(edges, adj);
        
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        vector<bool> visited(V, false);
        
        vector<pair<int, int>> MST;
        int sum = 0;
        pq.push({0, 0, -1});
        
        while(!pq.empty()){
            vector<int> top = pq.top();
            pq.pop();
            int wt = top[0], node = top[1], parent = top[2];
            if(!visited[node]){
                visited[node] = true;
                for(auto i : adj[node]){
                    int childNode = i.first;
                    if(!visited[childNode]){
                        pq.push({i.second, childNode, node});
                    }
                }
                if(parent != -1){
                    sum += wt;
                    MST.push_back({node, parent});
                }
            }
        }
        
        return sum;
    }
};

## **Time Complexity**
* An **adjacency list** → `O(V + E)` to store.
* A **priority queue** (min-heap) with `{wt, node, parent}` tuples.
**Step-by-step:**
1. **Building adjacency list:**
   Each edge is inserted twice (once for each direction) →
   `O(E)` time.
2. **Main loop:**
   * Each vertex gets visited once → `O(V)`.
   * Each edge `(u, v)` can cause at most **one push** into the PQ when explored from `u`.
   * Each push/pop from PQ is `O(log E)` because PQ size can be at most `O(E)` in worst case.
   Total:
   O((V + E) log E)
   Since in a connected graph `E ≥ V - 1`, we often write this as:
   O(E log V) (because `log E` ≈ `log V` in sparse graphs).

## **Space Complexity**
1. **Adjacency list:** `O(V + E)`
2. **Visited array:** `O(V)`
3. **Priority queue:** up to `O(E)` entries in worst case.
4. **MST storage:** `O(V)` edges stored.
**Total:**
O(V + E)
✅ **Final:**
* **Time Complexity:** `O(E log V)`
* **Space Complexity:** `O(V + E)`

--------------------------------------------------------------------------------------------------------------------------------------------

bool customComparison(vector<int> a, vector<int> b)
{
    return a[2] < b[2]; // it sorts in ascending order
}

class DisjointSet{
    vector<int> parent, rank;
public:
    DisjointSet(int n){
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i <= n; i++){
            parent[i] = i;
        }
    }
    
    int findUPar(int node){
        if(node == parent[node]) return node;
        // return findUParent(parent[node]); -> will take logN
        return parent[node] = findUPar(parent[node]); // path compression
    }
    
    void unionByRank(int u, int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u == ulp_v) return;
        
        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_v] < rank[ulp_u]){
            parent[ulp_v] = ulp_u;
        }
        else{
            parent[ulp_v] = ulp_u;
            rank[ulp_u] ++;
        }
    }
    
};

class Solution {
  public:
    int kruskalsMST(int V, vector<vector<int>> &edges) {
        // E no. of edges
        // ElogE;
        sort(edges.begin(), edges.end(), customComparison);
        vector<pair<int, int>> MST;
        int sum = 0;
        DisjointSet ds(V);
        // E * 4 * alpha * 2 (*2 because undirected)
        for(auto edge : edges){
            int edge1 = edge[0], edge2 = edge[1];
            if(ds.findUPar(edge1) != ds.findUPar(edge2)){
                sum += edge[2];
                MST.push_back({edge1, edge2});
                ds.unionByRank(edge1, edge2);
            }
        }
        return sum;
    }
};

TC - ElogE + E * 4 * alpha * 2
SC - E * 4 * alpha * 2