/*
===========================================
🧮 MODULO ARITHMETIC CHEAT SHEET (CP/DSA)
===========================================

✅ BASICS:
---------
Let MOD = 1e9 + 7 (or any prime)
All arithmetic is done modulo MOD.

Addition:
  (a + b) % MOD

Subtraction:
  (a - b + MOD) % MOD  // to avoid negative results

Multiplication:
  (1LL * a * b) % MOD  // cast to long long to prevent overflow

Division:
  (a / b) % MOD is NOT allowed directly!
  Use modular inverse:
    (a * modInverse(b)) % MOD

Exponentiation:
  (a^b) % MOD
  Use binary exponentiation for large b.

--------------------------------------------
🔢 1. MODULAR FACTORIAL
--------------------------------------------
long long factorial(int n) {
    long long res = 1;
    for (int i = 2; i <= n; i++) {
        res = (res * i) % MOD;
    }
    return res;
}

--------------------------------------------
🚀 2. MODULAR EXPONENTIATION (a^b % MOD)
--------------------------------------------
long long modPow(long long a, long long b, int mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

--------------------------------------------
🔁 3. MODULAR INVERSE (Fermat's Little Theorem)
--------------------------------------------
Only works if MOD is prime.

long long modInverse(long long a, int mod) {
    return modPow(a, mod - 2, mod);
}

--------------------------------------------
🔢 4. SUM OF SUBARRAY MINIMUMS (Leetcode 907)
--------------------------------------------
Correct use of modulo in multiplication:

long long contrib = (1LL * arr[i] * left) % MOD;
contrib = (contrib * right) % MOD;
sum = (sum + contrib) % MOD;

--------------------------------------------
📐 5. SUM OF ALL SUBARRAY PRODUCTS
--------------------------------------------
int sumSubarrayProducts(vector<int>& arr) {
    long long result = 0, prev = 0;
    for (int i = 0; i < arr.size(); i++) {
        prev = (prev * arr[i] + arr[i]) % MOD;
        result = (result + prev) % MOD;
    }
    return result;
}

--------------------------------------------
🧠 6. POWER SUM: 1^k + 2^k + ... + n^k
--------------------------------------------
long long sumOfPowers(int n, int k) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = (sum + modPow(i, k, MOD)) % MOD;
    }
    return sum;
}

--------------------------------------------
⚠️ COMMON MISTAKES TO AVOID:
--------------------------------------------
// ❌ May overflow:
long long res = a * b * c % MOD;

// ✅ Safe:
long long res = (1LL * a * b) % MOD;
res = (res * c) % MOD;

--------------------------------------------
📌 FINAL TIPS:
--------------------------------------------
1. Always use 1LL when multiplying to promote to 64-bit.
2. Always reduce modulo at every step in long chains.
3. Prefer MOD = 1e9 + 7 or 998244353 (both primes).
4. Modular inverse is essential for division.
5. Subtraction can be negative — always add MOD before taking %.

*/
