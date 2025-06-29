/*
Assignment 1 Q-16
https://practice.geeksforgeeks.org/problems/largest-prime-factor2601/1

Given a number n, your task is to find the largest prime factor of n.

Examples:
Input: n = 5
Output: 5
Explanation: The prime factorization of 5 is just 5. Therefore, the largest prime factor is 5.

Input: n = 24
Output: 3
Explanation: The prime factorization of 24 is 23×3. Among the prime factors (2, 3), the largest is 3.

Input: n = 13195
Output: 29
Explanation: The prime factorization of 13195 is 5×7×13×29. The largest prime factor is 29.

Constraints:
2 <= n <= 10^9
*/

class Solution {
    vector<int> generatePrimes(int n){
        int limit = sqrt(n);
        vector<bool> v(limit + 1, true);
        vector<int> prime;
        
        for(int i = 2; i * i <= limit; i++){
            if(v[i]){
                for(int j = i * i; j <= limit; j += i) v[j] = false;
            }
        }
        
        for(int i = 2; i <= limit; i++){
            if(v[i]) prime.push_back(i);
        }
        
        return prime;
    }
  public:
    int largestPrimeFactor(int n) {
        // code here
        vector<int> prime = generatePrimes(n);
        int maxFactor = 1;
        for(int i = 0; i < prime.size() && n > 1; i++){
            while(n > 1 && n % prime[i] == 0) n /= prime[i];
            maxFactor = prime[i];
        }
        return (n == 1) ? maxFactor : n;
    }
};
