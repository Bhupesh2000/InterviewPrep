/*
Assignment 10 Q7
https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1

Given an integer array arr[] and a number k. Find the count of distinct elements in every window of size k in the array.

Examples:
Input: arr[] = [1, 2, 1, 3, 4, 2, 3], k = 4
Output:  [3, 4, 4, 3]
Explanation: Window 1 of size k = 4 is 1 2 1 3. Number of distinct elements in this window are 3. 
Window 2 of size k = 4 is 2 1 3 4. Number of distinct elements in this window are 4.
Window 3 of size k = 4 is 1 3 4 2. Number of distinct elements in this window are 4.
Window 4 of size k = 4 is 3 4 2 3. Number of distinct elements in this window are 3.

Input: arr[] = [4, 1, 1], k = 2
Output: [2, 1]
Explanation: Window 1 of size k = 2 is 4 1. Number of distinct elements in this window are 2. 
Window 2 of size k = 2 is 1 1. Number of distinct elements in this window is 1. 

Input: arr[] = [1, 1, 1, 1, 1], k = 3
Output: [1, 1, 1]

Constraints:
1 <= k <= arr.size() <= 10^5
1 <= arr[i] <= 10^5
*/

class Solution {
  public:
    vector<int> countDistinct(vector<int> &arr, int k) {
        // code here.
        vector<int> ans;
        unordered_map<int, int> freq;
        int count = 0;
        for(int i = 0; i < k; i++){
            freq[arr[i]] ++;
            if(freq[arr[i]] == 1) count ++;
        }
        ans.push_back(count);
        for(int i = 0, j = k; j < arr.size(); i++, j++){
            freq[arr[i]] --;
            if(freq[arr[i]] == 0) count --;
            freq[arr[j]] ++;
            if(freq[arr[j]] == 1) count ++;
            ans.push_back(count);
        }
        return ans;
    }
};
TC - O(N), SC - O(k) can be reduced by deleting elements with freq 0 / O(N) in worst case when all no. are unique and k = n

Another approach is brute force by finding all the unique elements in 1 single window
TC - O(N * k), SC - O(1) 

