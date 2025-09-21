/*
Assignment-3 Q4

Given an integer n, return true if it is a power of two. Otherwise, return false.
An integer n is a power of two, if there exists an integer x such that n == 2x.

Example 1:
Input: n = 1
Output: true
Explanation: 20 = 1

Example 2:
Input: n = 16
Output: true
Explanation: 24 = 16

Example 3:
Input: n = 3
Output: false
 
Constraints:
-2^31 <= n <= 2^31 - 1


Loop solution

bool isPowerOfTwo(int n) {
    for(int i = 0; i <= 31; i++){
        if(n == (1 << i)) return true;
        if(n < (1 << i)) break;
    }
    return false;
}

--------------------------------------------------------------------------------------------------------------------------------------------

Without loop (using &)

bool isPowerOfTwo(int n) {
    return n>0 && ((n)&(n-1))==0;
}