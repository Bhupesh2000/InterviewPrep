/*
Count the number of set bits.
Eg
Input 1 - 16(1 0 0 0 0)
Output 1 - 1
Input 2 - 13(1 1 0 1)
Output 2 - 3
*/

Approach 1 - Divide by 2 till N > 1 and find the rem. each time. Each time rem == 1, increase the cnt
    1. n % 2 = n & 1
    2. n / 2 = n >> 1
int countSetBits(int n){
    int cnt = 0;
    while(n > 1){
        cnt += (n & 1);
        n >> 1;
    }
    if(n == 1) cnt ++;
    return cnt;
}

** Bitwise operations are faster than normal arithematic operations

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - Inbuilt C++ funcion -> __builtin_popcount(n)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 3 - do n = n & (n - 1), till n > 0
int countSetBits(int n){
    int cnt = 0;
    while(n > 0){
        n = n & (n - 1);
        cnt ++
    }
    return cnt;
}
TC - O(no. of set bits), worst case - O(31)

Approach 3 is better than Approach 1 in avg cases
