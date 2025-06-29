Problem Statement -
Find the Kth prime number.
K <= 5 * 10^6

So the problem is if we declare the array of N = 10^8, this will probably give TLE because first you will make the sieve of N and then run for on that sieve for 5 * 10^6th prime.

So better option will be to first print what is the 5 * 10^6th prime and then just update your code for N = Kth prime number

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

    int limit = 5000000;
    int cnt = 0, size = 0;
    for(int i = 2; i <= N; i++){
        if(sieve[i])
            cnt ++;
        if(cnt == limit){
            size = i;
            break;
        }
    }

    cout << size << endl;
}

The size will be the 5 * 10^6 th prime number which come out to be 86028121.
Now the updated code will be


int N = 86028121;
bool sieve[N + 1];
vector<int> dp;

void createSieve(){
    for(int i = 2; i <= N; i++)
        sieve[i] = true;

    for(int i = 2; i <= N; i++){
        if(sieve[i]){
            dp.push_back(i);
            for(int j = 2 * i; j <= N; j += i){
                sieve[j] = false;
            }
        }
    }
}

Now my ith index of dp will be (i + 1)th prime number

