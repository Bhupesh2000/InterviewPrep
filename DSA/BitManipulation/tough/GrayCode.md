/*
Assignment 10 Q16
https://leetcode.com/problems/gray-code/

An n-bit gray code sequence is a sequence of 2n integers where:
Every integer is in the inclusive range [0, 2n - 1],
The first integer is 0,
An integer appears no more than once in the sequence,
The binary representation of every pair of adjacent integers differs by exactly one bit, and
The binary representation of the first and last integers differs by exactly one bit.
Given an integer n, return any valid n-bit gray code sequence.


Example 1:
Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
[0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
- 00 and 10 differ by one bit
- 10 and 11 differ by one bit
- 11 and 01 differ by one bit
- 01 and 00 differ by one bit

Example 2:
Input: n = 1
Output: [0,1]
 
Constraints:
1 <= n <= 16
*/

Approach 1 -
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<string> grayCodeString = grayCodeHelper(n);
        vector<int> ans;
        for(string str : grayCodeString){
            int a = stoi(str, 0, 2);
            ans.push_back(a);
        }
        return ans;
    }
    vector<string> grayCodeHelper(int n){
        if(n == 1) return vector<string>{"0", "1"};
        vector<string> ans;
        vector<string> temp = grayCodeHelper(n - 1);
        int m = temp.size();
        for(int i = 0; i < m; i++){
            ans.push_back("0" + temp[i]);
        }
        for(int i = m - 1; i >= 0; i--){
            ans.push_back("1" + temp[i]);
        }
        return ans;
    }
};

🕒 Time Complexity
1. grayCodeHelper(n):
At each level of recursion:
You double the number of strings (2^n total in the end).
Each string has length n.
Total work at each level: appending '0' and '1' to strings of length up to n.

🧮 Total time:
Building all strings: O(2ⁿ × n)
Converting binary strings to integers via stoi: O(2ⁿ × n) again.

✅ Total Time Complexity = O(2ⁿ × n)

🧠 Space Complexity
1. Recursive call stack:
Depth = n → O(n)
2. Generated strings:
2^n strings of length n → O(2ⁿ × n)
3. Final integer vector:
2^n integers → O(2ⁿ)

✅ Total Space Complexity = O(2ⁿ × n) (dominated by string list)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 -
The i-th Gray code for a given i (from 0 to 2ⁿ - 1) can be directly computed using:
gray(i) = i ^ (i >> 1);

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        int size = 1 << n; // 2^n
        for (int i = 0; i < size; ++i) {
            result.push_back(i ^ (i >> 1));
        }
        return result;
    }
};

| Metric           | Value     |
| ---------------- | --------- |
| Time Complexity  | **O(2ⁿ)** |
| Space Complexity | **O(2ⁿ)** |
