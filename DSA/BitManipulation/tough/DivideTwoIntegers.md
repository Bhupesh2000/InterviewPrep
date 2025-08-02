/*
https://leetcode.com/problems/divide-two-integers/description/

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
Return the quotient after dividing dividend by divisor.
Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−2^31, 2^31 − 1]. For this problem, if the quotient is strictly greater than 2^31 - 1, then return 2^31 - 1, and if the quotient is strictly less than -2^31, then return -2^31.

Example 1:
Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.
Example 2:
Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.
 
Constraints:
-2^31 <= dividend, divisor <= 2^31 - 1
divisor != 0
*/

Approach 1 - dividend = 22, divisor = 3
Writing it as 3 + 3 + 3 + 3 + 3 + 3 + 3(count these number of 3s).
TC ->O(dividend)(when divisor is 1), SC - O(1)

Approach 2 - 
class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == divisor) return 1;
        bool sign = true;
        if(dividend < 0) sign = !sign;
        if(divisor < 0) sign = !sign;
        long n = abs((long) dividend), d = abs((long) divisor);
        long quotient = 0;
        while(n >= d){
            int cnt = 0;
            while(n >= (d << (cnt + 1))) cnt++;
            quotient += 1 << cnt;
            n -= (d << cnt);
        }
        if(quotient == (1 << 31)) return sign ? INT_MAX : INT_MIN;
        return sign ? quotient : quotient * -1;
    }
};

TC - O((log N)^2), SC - O(1)