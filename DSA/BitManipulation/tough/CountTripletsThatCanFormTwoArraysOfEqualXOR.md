/*
Assignment 10 Q13
https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/description/

Given an array of integers arr.
We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
Let's define a and b as follows:
a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
Note that ^ denotes the bitwise-xor operation.
Return the number of triplets (i, j and k) Where a == b.

Example 1:
Input: arr = [2,3,1,6,7]
Output: 4
Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)

Example 2:
Input: arr = [1,1,1,1,1]
Output: 10
 
Constraints:
1 <= arr.length <= 300
1 <= arr[i] <= 10^8
*/

Approach 1 - using 3 variables i, j, k
Each variable used to define 2 arrays(i to j - 1, j to k)
Calculate the xor from i to j - 1 and j to k and check if they are equal
TC - O(n^4), SC - O(1)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - update the above approach as to keep the running xor rather than calculating each time
TC - O(n^3), SC- O(1)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 -
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        vector<int> prefixXOR(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixXOR[i + 1] = prefixXOR[i] ^ arr[i];
        }
        
        int count = 0;
        for (int i = 0; i < n; ++i) {
            for (int k = i + 1; k < n; ++k) {
                if (prefixXOR[i] == prefixXOR[k + 1]) {
                    count += (k - i);  // (number of j such that i < j <= k)
                }
            }
        }
        return count;
    }
};

TC - O(n^2), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - using a hashmap(2 passes)
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int ans = 0, n = arr.size();
        vector<int> prefXor(n + 1, 0);
        for(int i = 0; i < n; i++){
            prefXor[i + 1] = prefXor[i] ^ arr[i];
        }
        unordered_map<int, int> sumOfI, countOfXor;
        sumOfI[0] = 0; countOfXor[0] = 1;
        for(int k = 1; k <= n; k++){
            int x = prefXor[k];
            ans += (k - 1) * countOfXor[x] -  sumOfI[x];
            countOfXor[x] ++;
            sumOfI[x] += k;
        }
        return ans;
    }
};

TC - O(2 * n), SC - O(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 4 - using a hashmap(1 pass)
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int ans = 0, n = arr.size();
        vector<int> prefXor(n + 1, 0);
        unordered_map<int, int> sumOfI, countOfXor;
        sumOfI[0] = 0; countOfXor[0] = 1;
        for(int k = 1; k <= n; k++){
            prefXor[k] = prefXor[k - 1] ^ arr[k - 1];
            int x = prefXor[k];
            ans += (k - 1) * countOfXor[x] -  sumOfI[x];
            countOfXor[x] ++;
            sumOfI[x] += k;
        }
        return ans;
    }
};

TC - O(2 * n), SC - O(n)