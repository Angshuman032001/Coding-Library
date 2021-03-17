std::vector<bool> isPrime;
std::vector<int> sFactor,primes;
 
void sieve(int n)
{
    isPrime.assign(n+1,true);
    sFactor.assign(n+1,0);
    isPrime[0]=isPrime[1]=false;
    primes={};
    for(int i=2;i<=n;i++)
    {
        if(isPrime[i])
        {
            sFactor[i]=i;
            primes.push_back(i);
            for(int j=i*i;j<=n;j+=i)
            if(isPrime[j])
            {
                isPrime[j]=false;
                sFactor[j]=i;
            }
        }
    }
}

vector<bool> segmented_sieve(int l, int r){
    /*first generate all primes till sqrt(r)*/
    vector<bool>result(r - l + 1, true); /*first initialize every element as true*/
    for(auto i : primes){
        for(int j = max(i*i, (l + i - 1)/i*i);j<=r;j+=i) result[j - l] = false;
    }
    if(l == 1) result[0] = false;
    return result;
}

