Problem Statement - 
N inputs, for each input return true if prime else false;
N <= 10^6.
K <= 10^6(Max input value).

So if we use traditional logic by running the loop till sqrt(N), time will be 10^6 * 10^3 = 10^9(TLE).

So we use sieve in which we pre compute the results and use it for each n

int N = 1000000;
bool sieve[1000001];

void createSieve(){
    for(int i = 2; i <= N; i++)
        sieve[i] = true;

    for(int i = 2; i <= N; i++){
        if(sieve[i]){
            for(int j = 2 * i; j <= N; j += i){
                sieve[j] = false;
            }
        }
    }
}

1st optimisation - for each j, we don't need to start for j = 2 * i, but rather i * i, because all the lower values will be already marked by lesser i

int N = 1000000;
bool sieve[1000001];

void createSieve(){
    for(int i = 2; i <= N; i++)
        sieve[i] = true;

    for(int i = 2; i <= N; i++){
        if(sieve[i]){
            for(int j = i * i; j <= N; j += i){
                sieve[j] = false;
            }
        }
    }
}

2nd optimisation - we don't need to take our i to N, because i <= sqrt(N) will already mark all the values till N.
eg N = 25, for i = 6, it doesnot make any sense, because the inner loop will start from j = 36.

int N = 1000000;
bool sieve[1000001];

void createSieve(){
    for(int i = 2; i <= N; i++)
        sieve[i] = true;

    for(int i = 2; i * i <= N; i++){
        if(sieve[i]){
            for(int j = i * i; j <= N; j += i){
                sieve[j] = false;
            }
        }
    }
}

TC - O(N log log N) equivalent to O(N), log log N is very small
This approximation comes from number theory

the max size of int type array inside main() -> 10^6
the max size of bool type array inside main() -> 10^7

the max size of int type array globally -> 10^7
the max size of bool type array globally -> 10^8
