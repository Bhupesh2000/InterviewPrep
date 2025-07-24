/*
https://www.geeksforgeeks.org/problems/k-closest-elements3619/1

You are given a sorted array arr[] of unique integers, an integer k, and a target value x. Return exactly k elements from the array closest to x, excluding x if it exists.
An element a is closer to x than b if:
|a - x| < |b - x|, or
|a - x| == |b - x| and a > b (i.e., prefer the larger element if tied)
Return the k closest elements in order of closeness.

Examples:
Input: arr[] = [1, 3, 4, 10, 12], k = 2, x = 4
Output: 3 1
Explanation: 4 is excluded, Closest elements to 4 are: 3 (1), 1 (3). So, the 2 closest elements are: 3 1

Input: arr[] = [12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56], k = 4, x = 35
Output: 39 30 42 45
Explanation: First closest element to 35 is 39.
Second closest element to 35 is 30.
Third closest element to 35 is 42.
And fourth closest element to 35 is 45.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ k ≤ arr.size()
1 ≤ x ≤ 10^6
1 ≤ arr[i] ≤ 10^6
*/

Approach 1 - using max-heap

struct Compare{
    bool operator()(const pair<int,int>& a, const pair<int,int>& b){
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    }
};
class Solution {
  public:
    vector<int> printKClosest(vector<int> arr, int k, int x) {
        // Code here
        int n = arr.size();
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
        
        for(int i = 0; i < k; i++){
            if(arr[i] == x) continue;
            pq.push({abs(arr[i] - x), arr[i]});
        }
        
        for(int i = k; i < n; i++){
            if(arr[i] == x) continue;
            int diff = abs(arr[i] - x);
            if(pq.size() < k){
                pq.push({diff, arr[i]});
            }
            else if(pq.top().first >= diff){
                pq.pop();
                pq.push({diff, arr[i]});
            }
        }
        
        vector<int> ans(k);
        for(int i = k - 1; i >= 0; i--){
            ans[i] = pq.top().second;
            pq.pop();
        }
        
        return ans;
    }
};

TC - O(NlogK), SC - O(K)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using a new vector which will store a pair of difference and arr[i]. Sort it and return first k elements.
TC - O(NlogN) -> for sorting diff + O(N) -> for getting all the diff + O(K) -> for getting first k elements
SC - O(N) -> for storing diff

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - built upon the Approach 2. using 2 pointers

class Solution {
  public:
    vector<int> printKClosest(vector<int> arr, int k, int x) {
        // Code here
        int n = arr.size();
        int minDiff = INT_MAX, ind = -1;
        for(int i = 0; i < n; i++){
            int diff = abs(arr[i] - x);
            if(ind == -1){
                minDiff = diff;
                ind = i;
            }
            else if(diff > minDiff) break;
            else{
                minDiff = diff;
                ind = i;
            }
        }
        
        int i = ind, j = ind + 1;
        vector<int> ans;
        while(i >= 0 && j < n && ans.size() < k){
            if(arr[i] == x){
                i --;
                continue;
            }
            int diff1 = abs(x - arr[i]);
            int diff2 = abs(x - arr[j]);
            
            if(diff1 < diff2){
                ans.push_back(arr[i]);
                i --;
            }
            else{
                ans.push_back(arr[j]);
                j ++;
            }
        }
        while(i >= 0 && ans.size() < k){
            ans.push_back(arr[i]);
            i --;
        }
        while(j < n && ans.size() < k){
            ans.push_back(arr[j]);
            j ++;
        }
        
        return ans;
    }
};

TC - O(N) -> for finding minDiff + O(K) -> for getting k elements
SC - O(1)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - Built upon approach 3
Since the array is sorted, for finding minDiff, we directly search binary search
TC - O(log N) -> for finding minDiff + O(K) -> for getting k elements
SC - O(1)