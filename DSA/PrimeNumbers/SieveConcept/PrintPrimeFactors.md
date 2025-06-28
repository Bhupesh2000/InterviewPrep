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