/*
Given an array arr. Find the sum of all subarrays of the array since the sum could be very large print the sum modulo (109+7).

Examples:

Input: arr[] = [1, 2, 3]
Output: 20
Explanation: All subarray sums are: [1] = 1, [2] = 2, [3] = 3, [1,2] = 3, [2,3] = 5, [1,2,3] = 6. Thus total sum is 1+2+3+3+5+6 = 20.
Input: arr[] = [1, 3]
Output: 8
Explanation: All subarray sums are: [1] = 1 [3] = 3 [1,3] = 4. Thus total sum is 1+3+4 = 8.
Expected Time Complexity: O(n)
Expected Auxiliary Space: O(1)

Constraints :
1 ≤ arr.size() ≤ 106
1 ≤ arr[i] ≤ 109
*/

// User function template for C++

class Solution {
  public:
    long long subarraySum(vector<int>& arr) {
        long long sum = 0;
        int n = arr.size();
        long long mod = 1e9 + 7;

        for (int i = 0; i < n; i++) {
            long long term = (1LL * (i + 1) % mod * (n - i) % mod) % mod;
            term = (term * arr[i]) % mod;
            sum = (sum + term) % mod;
        }

        return sum;
    }
};