/*
https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1

Given an array arr[], where each element is at most k away from its target position, you need to sort the array optimally.
Note: You need to change the given array arr[] in place.

Examples:

Input: arr[] = [6, 5, 3, 2, 8, 10, 9], k = 3
Output: [2, 3, 5, 6, 8, 9, 10]
Explanation: The sorted array will be 2 3 5 6 8 9 10
Input: arr[]= [1, 4, 5, 2, 3, 6, 7, 8, 9, 10], k = 2
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
Explanation: The sorted array will be 1 2 3 4 5 6 7 8 9 10
Don't use the inbuilt sort() function for this question.

Constraints:
1 ≤ arr.size() ≤ 10^6
0 ≤ k < arr.size()
1 ≤ arr[i] ≤ 10^6
*/

class Solution {
  public:
    void nearlySorted(vector<int>& arr, int k) {
        // code
        int n = arr.size();
        if(n <= 1 || k == 0) return;
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i <= k; i++){
            pq.push(arr[i]);
        }
        int i = 0;
        while(i < n - k){
            arr[i] = pq.top();
            pq.pop();
            i ++;
            if(i < n - k) pq.push(arr[i + k]);
        }
        while(!pq.empty()){
            arr[i] = pq.top();
            pq.pop();
            i ++;
        }
    }
};

TC - O(NlogK), SC - O(K)