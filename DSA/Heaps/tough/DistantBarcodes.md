/*
Assignment 8 Q7
https://practice.geeksforgeeks.org/problems/job-sequencing-problem/0

In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.

Example 1:
Input: barcodes = [1,1,1,2,2,2]
Output: [2,1,2,1,2,1]

Example 2:
Input: barcodes = [1,1,1,1,2,2,3,3]
Output: [1,3,1,3,1,2,1,2]
 
Constraints:
1 <= barcodes.length <= 10000
1 <= barcodes[i] <= 10000
*/

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> freq;
        for(int it : barcodes){
            freq[it] ++;
        }
        vector<int> res;
        priority_queue<pair<int, int>> pq;
        for(auto it : freq){
            pq.push({it.second, it.first});
        }

        while(!pq.empty()){
            pair<int, int> top1 = pq.top();
            pq.pop();
            res.push_back(top1.second);
            if(!pq.empty()){
                pair<int, int> top2 = pq.top();
                pq.pop();
                res.push_back(top2.second);
                if(top2.first > 1) pq.push({top2.first - 1, top2.second});
            }
            if(top1.first > 1) pq.push({top1.first - 1, top1.second});
        }

        return res;
    }
};