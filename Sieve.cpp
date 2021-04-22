std::vector<bool> isPrime;
std::vector<int> sFactor,primes;
 
void sieve(int n) {
    isPrime.assign(n+1,true);
    sFactor.assign(n+1,0);
    isPrime[0]=isPrime[1]=false;
    primes={};
    for(int i=2;i<=n;i++) {
        if(isPrime[i]) {
            sFactor[i]=i;
            primes.push_back(i);
            for(int j=i*i;j<=n;j+=i)
            if(isPrime[j]) {
                isPrime[j]=false;
                sFactor[j]=i;
            }
        }
    }
}

// Prime factorizes n in worst case O(sqrt n / log n). Requires having run `sieve` up to at least sqrt(n).
// If we've run `sieve` up to at least n, takes O(log n) time.
vector<pair<int64_t, int>> prime_factorize(int64_t n) {
    int64_t sieve_max = int64_t(sFactor.size()) - 1;
    assert(1 <= n && n <= sieve_max * sieve_max);
    vector<pair<int64_t, int>> result;
 
    if (n <= sieve_max) {
        while (n != 1) {
            int64_t p = sFactor[n];
            int exponent = 0;
 
            do {
                n /= p;
                exponent++;
            } while (n % p == 0);
 
            result.emplace_back(p, exponent);
        }
 
        return result;
    }
 
    for (int64_t p : primes) {
        if (p * p > n)
            break;
 
        if (n % p == 0) {
            result.emplace_back(p, 0);
 
            do {
                n /= p;
                result.back().second++;
            } while (n % p == 0);
        }
    }
 
    if (n > 1)
        result.emplace_back(n, 1);
 
    return result;
}
