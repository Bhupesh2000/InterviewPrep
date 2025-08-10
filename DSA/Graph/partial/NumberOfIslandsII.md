/*
https://www.naukri.com/code360/problems/largest-island_840701?leftPanelTabValue=SUBMISSION

You are given two integers 'n' and 'm', the dimensions of a grid. The coordinates are from (0, 0) to (n - 1, m - 1).
The grid can only have values 0 and 1.
The value is 0 if there is water and 1 if there is land.
An island is a group of ‘1’s such that every ‘1’ has at least another ‘1’ sharing a common edge.
You are given an array 'queries' of size 'q'.
Each element in 'queries' contains two integers 'x' and 'y', referring to the coordinates in the grid.
Initially, the grid is filled with 0, which means only water and no land.
At each query, the value of 'grid' at (x, y) becomes 1, which means it becomes land.
Find out, after each query, the number of islands in the grid.

Example :
Input: 'n' = 3, 'm' = 4
'queries' = [[1, 1], [1, 2], [2, 3]]
Output: [1, 1, 2]
Explanation:
Initially, the grid was:
0 0 0 0
0 0 0 0
0 0 0 0
After query (1, 1):
0 0 0 0
0 1 0 0
0 0 0 0
There is one island having land (1, 1).
After query (1, 2):
0 0 0 0
0 1 1 0
0 0 0 0
Since (1, 1) and (1, 2) share a common edge, they form one island. So there is one island having lands (1, 1) and (1, 2).
After query (2, 3):
0 0 0 0
0 1 1 0
0 0 0 1
Now there are two islands, one having lands (1, 1) and (1, 2), and another having land (2, 3).
So the number of islands after each query is [1, 1, 2].
Detailed explanation ( Input/output format, Notes, Images )

Sample Input 1:
3 4
3
1 1
1 2
2 3
Sample Output 1:
1 1 2
Explanation of sample input 1 :
Initially, the grid was:
0 0 0 0
0 0 0 0
0 0 0 0
After query (1, 1):
0 0 0 0
0 1 0 0
0 0 0 0
There is one island having land (1, 1).
After query (1, 2):
0 0 0 0
0 1 1 0
0 0 0 0
Since (1, 1) and (1, 2) share a common edge, they form one island. So there is one island having lands (1, 1) and (1, 2).
After query (2, 3):
0 0 0 0
0 1 1 0
0 0 0 1
Now there are two islands, one having lands (1, 1) and (1, 2), and another having land (2, 3).
So the number of islands after each query is [1, 1, 2].

Sample Input 2:
3 5
3
1 1
1 3
1 2
Sample Output 2:
1 2 1

Expected time complexity :
The expected time complexity is O(n * m + q).

Constraints :
1 <= 'n', 'm' <= 1000
1 <= 'q' <= 10 ^ 4
0 <= 'x' < 'n'
0 <= 'y' < 'm'
All the (x, y) pairs are unique.
*/

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

vector<int> numberOfIslandII(int n, int m, vector<vector<int>>& queries, int q)
{
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<int> ans;
    int cnt = 0;
    DisjointSet ds(n * m);
    for(int i = 0; i < queries.size(); i++){
        int x = queries[i][0], y = queries[i][1];
        if(visited[x][y]){
            ans.push_back(cnt);
            continue;
        }
        visited[x][y] = true;
        cnt ++;
        int number1 = x * m + y;
        if(x > 0 && visited[x - 1][y]){
            int number2 = (x - 1) * m + y;
            if(ds.findUPar(number1) != ds.findUPar(number2)){
                cnt --;
                ds.unionByRank(number1, number2);
            }
        }
        if(y > 0 && visited[x][y - 1]){
            int number2 = x * m + (y - 1);
            if(ds.findUPar(number1) != ds.findUPar(number2)){
                cnt --;
                ds.unionByRank(number1, number2);
            }
        }
        if(x < n - 1 && visited[x + 1][y]){
            int number2 = (x + 1) * m + y;
            if(ds.findUPar(number1) != ds.findUPar(number2)){
                cnt --;
                ds.unionByRank(number1, number2);
            }
        }
        if(y < m - 1 && visited[x][y + 1]){
            int number2 = x * m + (y + 1);
            if(ds.findUPar(number1) != ds.findUPar(number2)){
                cnt --;
                ds.unionByRank(number1, number2);
            }
        }
        ans.push_back(cnt);
    }
    return ans;
}
