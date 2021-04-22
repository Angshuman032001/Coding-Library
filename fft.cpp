#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()

using namespace __gnu_pbds;
using namespace std;

#define deb(...) cerr << "[" << #__VA_ARGS__ << "] : [", DBG(__VA_ARGS__)
void DBG() { cerr << "]\n";}
template<typename T, typename ...Args> void DBG(T first, Args... args)
{cerr << first; if(sizeof...(args))cerr<<", "; DBG(args...); }


const int mod = 998244353, root = 565042129, root_1 = 950391366, root_pw = 1 << 20;

int mod_pow(long long a, int k) {
    long long p = 1;
    while(k) {
        if(k%2) p = p * a % mod;
        a = a * a % mod;
        k /= 2;
    }
    return p;
}

void fft(vector<int> & a, bool invert) {
    int n = a.size();

    /*for inplace fft*/
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n/2;
        for (; j & bit; bit /= 2) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = mod_pow(n, mod-2);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

vector<int> multiply(vector<int> const & a, vector<int> const & b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n *= 2;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] = 1LL * fa[i] * fb[i] % mod;
    fft(fa, true);
    return fa;
}

int32_t main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    int n, m; cin>>n>>m;
    std::vector<int>a(n), b(m);
    for(auto &x : a) cin>>x;
    for(auto &x : b) cin>>x;

    std::vector<int> c = multiply(a, b);
    for(int i = 0;i<n+m-1;i++) cout<<c[i]<<" ";
    cout<<"\n";

    return 0;

}