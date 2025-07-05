/*
Assignment 6 Q7
https://leetcode.com/problems/sum-of-subarray-minimums/description/

Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.

Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:
Input: arr = [11,81,94,43,3]
Output: 444

Constraints:

1 <= arr.length <= 3 * 10^4
1 <= arr[i] <= 3 * 10^4
*/

int Mod = pow(10, 9) + 7;
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int sum = 0;
        stack<int> st;
        for(int i = 0; i < arr.size(); i++){
            if(st.empty() || arr[st.top()] <= arr[i]) st.push(i);
            else{
                while(!st.empty() && arr[st.top()] > arr[i]){
                    int topIndex = st.top();
                    int right = i - topIndex;
                    st.pop();
                    int left = st.empty() ? (topIndex + 1) : (topIndex - st.top());
                    long long contrib = (1LL * arr[topIndex] * left) % Mod;
                    contrib = (contrib * right) % Mod;
                    sum = (sum + contrib) % Mod;
                }
                st.push(i);
            }
        }

        while(!st.empty()){
            int topIndex = st.top();
            int right = arr.size() - topIndex;
            st.pop();
            int left = st.empty() ? (topIndex + 1) : (topIndex - st.top());
            long long contrib = (1LL * arr[topIndex] * left) % Mod;
            contrib = (contrib * right) % Mod;
            sum = (sum + contrib) % Mod;
        }

        return sum % Mod;
    }
};

TC - O(N), SC - O(N).

Learn how to use module.