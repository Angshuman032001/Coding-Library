vec(bool) isPrime;
vi sFactor,primes;
 
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
            primes.pb(i);
            for(int j=i*i;j<=n;j+=i)
            if(isPrime[j])
            {
                isPrime[j]=false;
                sFactor[j]=i;
            }
        }
    }
}