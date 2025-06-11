/*
Given two arrays of integers a[] and b[], the task is to check if a pair of values (one value from each array) exists such that swapping the elements of the pair will make the sum of two arrays equal.

Examples :
Input: a[] = [4, 1, 2, 1, 1, 2], b[] = [3, 6, 3, 3]
Output: true
Explanation: Sum of elements in a[] = 11, Sum of elements in b[] = 15, To get same sum from both arrays, we can swap following values: 1 from a[] and 3 from b[]

Input: a[] = [5, 7, 4, 6], b[] = [1, 2, 3, 8]
Output: true
Explanation: We can swap 6 from array a[] and 2 from array b[]

Input: a[] = [3, 3], b[] = [6, 5, 6, 6]
Output: false

Constraints:
1 ≤ a.size() ≤ 106
1 ≤ b.size() ≤ 106
1 ≤ a[i] ≤ 103
1 ≤ b[i] ≤ 103
*/

class Solution {

  public:
    bool findSwapValues(vector<int>& a, vector<int>& b) {
        // Your code goes here
        int n = a.size(), m = b.size();
        int sum1 = 0, sum2 = 0;
        for(int i = 0; i < n; i++){
            sum1 += a[i];
        }
        for(int i = 0; i < m; i++){
            sum2 += b[i];
        }
        
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        int i = 0, j = 0;
        while(i < n && j < m){
            int swapSum1 = sum1 - a[i] + b[j];
            int swapSum2 = sum2 - b[j] + a[i];
            if(swapSum1 == swapSum2) return true;
            else if(swapSum1 > swapSum2) i ++;
            else j ++;
        }
        return false;
    }
};