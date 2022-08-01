// https://cp-algorithms.com/algebra/prime-sieve-linear.html
#include "bits/stdc++.h"

using namespace std;

const int N = 1e7 + 1;
vector<int>sFactor(N + 1), primes;

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    for(int i = 2;i<=N;i++){
        if(sFactor[i] == 0){
            sFactor[i] = i;
            primes.push_back(i);
        }
        for(int j = 0;j<int(primes.size()) && primes[j] <= sFactor[i] && i * primes[j] <= N; j++){
            sFactor[i * primes[j]] = primes[j];
        }
    }

    

}
