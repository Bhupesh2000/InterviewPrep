Problem Statement - 
Give a number of test cases T(very small T <= 10), and for each case two integers L and R(L, R <= 10^12), but (R - L <= 10^6).
Print all the primes b/w L and R.

We will use the concept of segmented sieve. In this the index 0 will point to L.

Step 1 - Get all primes till sqrt(R), because all the mutliples till R will be defined by the prime numbers <= sqrt(R).
Eg. R = 25, all the numbers till 25 are defined by primes <= 5. 7 * 7 = 49 > 25.

Step 2 - create a dummy array of size R - L + 1 and initiate all the values to 1.

Step 3 - Mark all the multiples of primes selected in step 1 in the (L to R) dummy array

int N = 1000000;
bool sieve[N + 1];

void createSieve(){
    for(int i = 0; i <= N; i++){
        sieve[i] = true;
    }

    for(int i = 2; i * i <= N; i++){
        if(sieve[i] == 1){
            for(int j = i * i; j <= N; j += i){
                sieve[j] = 1;
            }
        }
    }
}

vector<int> generatePrimes(int N){
    vector<int> ds;
    for(int i = 2; i <= N; i++){
        if(sieve[i]) ds.push_back(i);
    }
    return ds;
}

int main(){
    createSieve();
    int t;
    cin >> t;
    while(t --){
        int l, r;
        cin >> l >> r;
        // Step 1
        // generate primes till sqrt(R)
        vector<int> primes = generatePrimes(sqrt(R));

        // Step 2
        // create a dummy array of size (r - l + 1) and mark all the numbers as 1
        int dummy[r - l + 1];
        for(int i = 0; i < r - l + 1; i++){
            dummy[i] = 1;
        }

        // Step 3
        // Mark all the multiples of all the primes in the range [L, R] as 0.
        for(int pr : primes){
            int firstMutliple = (l / pr) * pr;
            if(firstMutliple < l) firstMutliple += pr;
            for(int i = max(firstMutliple, pr * pr); i <= r; i += pr){
                dummy[i - l] = 0;
            }
        }

        // Step 4
        // get all the primes in the range [L, R]
        for(int i = l; i <= r; i++){
            if(dummy[i - l] == 1) cout << i << " ";
        }
        cout << endl;
    }
}

TC - O(10^6) -> createSieve + O(10(t) * (10^6(generating primes) + 10^6(marking dummy array as 1) + 10^4(iterating primes * tc of inner loop which is not very constant because jumping is not ceratin))) equivalent to 10^7.

