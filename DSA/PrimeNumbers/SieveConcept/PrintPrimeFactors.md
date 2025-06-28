Print Prime Factors for N

for(int i = 1; i <= N; i ++){
    while(i % N == 0){
        cout << i << endl;
        N /= i;
    }
}

for this the worst case is O(N), for prime numbers

this can be reduced to sqrt(N)

for(int i = 1; i * i <= N; i ++){
    while(i % N == 0){
        cout << i << endl;
        N /= i;
    }
}
if(N > 1) cout << N; // required for some conditions, eg. N = 35, N = 13

for the above problem, if lets say n inputs are given, n <= 10^6, N <= 10^6.
So TC = O(n) * O(sqrt(N)) => 10^6 * 10^3 = 10^9 > 10^8. This will give TLE.
Hence something better is required

We will be using Sieve. Store the min prime factor of a number, in the array. then divide the number by its min prime factor
Max time taken for a getting all the prime factors will be logN, with base 2(2 is the min prime number, any prime factor bigger than 2 will take less time than this).

so total tc - O(N log log N) -> creating sieve + O(log N)

const int N = 1000000;
int sieve[N + 1];

void createSieve(){
    for(int i = 1; i <= N; i++){
        sieve[i] = i;
    }

    for(int i = 2; i * i <= N; i++){
        if(sieve[i] == i){
            for(int j = i * i; j <= N; j += i){
                if(sieve[j] == j) sieve[j] = i;
            } 
        }
    }
}

int main(){
    createSieve();
    int t;
    cin >> t;
    while(t --){
        int n;
        cin >> n;
        while(n > 1){
            cout << sieve[n] << " ";
            n /= sieve[n];
        }
        cout << endl;
    }
}