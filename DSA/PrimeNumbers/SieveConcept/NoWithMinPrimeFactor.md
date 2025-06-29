Problem Statement - Give a series of prime numbers(n). Find how many numbers in range [1, 10^6] have have min prime factor as n.

int N = 1000000;
int sieve[N + 1];

void createSieve(){
    for(int i = 2; i <= N; i++)
        sieve[i] = 1;

    for(int i = 2; i <= N; i++){
        if(sieve[i] == 1){
            for(int j = 2 * i; j <= N; j += i){
                if(sieve[j] != 0){
                    sieve[i] ++;
                    sieve[j] = 0;
                }
            }
        }
    }
}