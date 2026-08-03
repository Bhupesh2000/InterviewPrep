/*
Assignment 11 Q9
https://leetcode.com/problems/network-delay-time/description/

You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

Example 1:
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2

Example 2:
Input: times = [[1,2,1]], n = 2, k = 1
Output: 1

Example 3:
Input: times = [[1,2,1]], n = 2, k = 2
Output: -1
 
Constraints:
1 <= k <= n <= 100
1 <= times.length <= 6000
times[i].length == 3
1 <= ui, vi <= n
ui != vi
0 <= wi <= 100
All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
*/

class Solution {
    void createAdjList(vector<vector<int>>& times, vector<vector<pair<int, int>>>& adj){
        for(int i = 0; i < times.size(); i++){
            adj[times[i][0] - 1].push_back({times[i][1] - 1, times[i][2]});
        }
    }
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n);
        createAdjList(times, adj);

        vector<int> dist(n, INT_MAX);

        set<pair<int, int>> st;
        dist[k - 1] = 0;
        st.insert({0, k - 1});

        while(!st.empty()){
            pair<int, int> top = *st.begin();
            st.erase(top);
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

        int minDist = 0;
        for(int i : dist){
            if(i == INT_MAX) return -1;
            if(minDist < i) minDist = i;
        }
        return minDist;
    }
};
