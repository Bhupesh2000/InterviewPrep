/*
Assignment 10 Q14
https://www.hackerrank.com/contests/codeagon/challenges/bob-and-subarray-or/problem

Bob has an array arr having n integers. Bob wants to determine the addition of Bitwise OR of all the subarrays present in the array.
Note : Subarray of an array is a contiguous block of elements containing any number of elements from the array.
Note : Bitwise OR of a subarray containing a single element will be the element itself .
Compute the sum of the Bitwise OR of all the subarrays present in the array.

Input Format
First line of the input consists of single integer denoting .
Second line of the input consists of  spaced integers denoting integers of the array.

Constraints
1 < N < 10^5
1 <= arr[i] <= 10^8


Output Format
Output consists of single integer denoting the answer.
Sample Input 0
5
1 2 3 4 5 
Sample Output 0
71
Explanation 0
Subarray	Bitwise OR
{ 1 }	1
{ 1,2 }	3
{ 1,2,3 }	3
{ 1,2,3,4 }	7
{ 1,2,3,4,5 }	7
{ 2 }	2
{ 2,3 }	3
{ 2,3,4 }	7
{ 2,3,4,5 }	7
{ 3 }	3
{ 3,4 }	7
{ 3,4,5 }	7
{ 4 }	4
{ 4,5 }	5
{ 5 }	5
The summation of the Bitwise ORs is 71.

Sample Input 1
4
29 39 3292 324
Sample Output 1
21115
Explanation 1
Subarray	Bitwise OR
{ 29 }	29
{ 29,39 }	63
{ 29,39,3292 }	3327
{ 29,39,3292,324 }	3583
{ 39 }	39
{ 39,3292 }	3327
{ 39,3292,324 }	3583
{ 3292 }	3292
{ 3292,324 }	3548
{ 324 }	324
The summation of the Bitwise ORs is 21115.

Approach 1 -
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int sumOfBitwiseOR(vector<int>& nums){
    int n = nums.size();
    int sum = 0;
    for(int i = 0; i < n; i++){
        int bitwiseOR = 0;
        for(int j = i; j < n; j++){
            bitwiseOR |= nums[j];       // Extend the subarray
            sum += bitwiseOR;           // Add current OR to sum
        }
    }
    return sum;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    cout << sumOfBitwiseOR(v);
    return 0;
}
TC - O(n^2), SC - O(1)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2
#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int sumOfBitwiseOR(vector<int>& nums) {
    int n = nums.size();
    long long total = 0;

    for(int bit = 0; bit < 32; bit++) {
        int lastSet = -1;
        long long contrib = 0;

        for(int i = 0; i < n; i++) {
            if(nums[i] & (1 << bit)) {
                lastSet = i;
            }
            if(lastSet != -1) {
                contrib += (lastSet + 1); // subarrays ending at i with this bit set
            }
        }
        total += contrib * (1LL << bit);
    }

    return total;
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << sumOfBitwiseOR(nums) << endl;
    return 0;
}

| Metric           | Value                 |
| ---------------- | --------------------- |
| Time Complexity  | O(32 * N) ≈ O(N)     |
| Space Complexity | O(1) (ignoring input) |
