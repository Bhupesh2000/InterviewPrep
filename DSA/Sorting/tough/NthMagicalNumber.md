/*
Assignment 2 Q23
https://leetcode.com/problems/nth-magical-number/

A positive integer is magical if it is divisible by either a or b.
Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.

Example 1:
Input: n = 1, a = 2, b = 3
Output: 2
Example 2:
Input: n = 4, a = 2, b = 3
Output: 6
 
Constraints:
1 <= n <= 10^9
2 <= a, b <= 4 * 10^4
*/

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long mod = (long)(pow(10, 9) + 7);

        long left = min(a, b), right = long(min(a, b)) * n;
        long LCM = (a * b) /  __gcd(a, b);

        while(left < right){
            long mid = (left + right) / 2;
            if((mid / a + mid / b - mid / LCM) < n) left = mid + 1;
            else right = mid;
        }

        return (int)(left % mod);
    }
};