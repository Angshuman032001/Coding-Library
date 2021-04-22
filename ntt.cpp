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

const int N = 1e5 + 10, mod = 998244353, inf = 1e17;

template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;
private:
    
    int value;
 
    static int minv(int a, int m) {
        a %= m;
        assert(a);
        return a == 1 ? 1 : (int)(m - (int)(minv(m, a)) * (int)(m) / a);
    }
 
public:
 
    modnum() : value(0) {}
    modnum(int v_) : value((int)(v_ % MOD)) { if (value < 0) value += MOD; }
    explicit operator int() const { return value; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << (int)(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { int v_; in >> v_; n = modnum(v_); return in; }
 
    modnum power(modnum a, int b) const {
        modnum res = 1;
        while(b>0){
            if(b&1)
                res *= a;
            a=(a*a);
            b>>=1;
        }
        return res;
    }

    modnum inv() const {
        modnum res;
        res.value = minv(value, MOD);
        return res;
    }

    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.value = value ? MOD-value : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }
 
    modnum operator- () const {
        return neg();
    }
    modnum operator+ () const {
        return modnum(*this);
    }
 
    modnum& operator ++ () {
        value ++;
        if (value == MOD) value = 0;
        return *this;
    }
    modnum& operator -- () {
        if (value == 0) value = MOD;
        value --;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        value -= MOD-o.value;
        value = (value < 0) ? value + MOD : value;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        value -= o.value;
        value = (value < 0) ? value + MOD : value;
        return *this;
    }
    modnum& operator *= (const modnum& o) {
        value = (int)((int)(value) * (int)(o.value) % MOD);
        return *this;
    }
    modnum& operator /= (const modnum& o) {
        return *this *= o.inv();
    }
 
    friend modnum operator ++ (modnum& a, int32_t) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int32_t) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }

    friend bool operator == (const modnum& a, const modnum& b) { return a.value == b.value; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.value != b.value; }
    friend bool operator < (const modnum& a, const modnum& b) { return a.value < b.value; }
    friend bool operator > (const modnum& a, const modnum& b) { return a.value > b.value; }
    friend bool operator <= (const modnum& a, const modnum& b) { return a.value <= b.value; }
    friend bool operator >= (const modnum& a, const modnum& b) { return a.value >= b.value; }
};

using mint = modnum<mod>;

//set mod to correct value
template< typename mint>
struct NTT{

    vector<mint> dw, idw;
    int max_base;
    mint root;

    NTT() {
        assert(mod >= 3 && mod % 2 == 1);
        auto tmp = mod - 1;
        max_base = 0;
        while(tmp % 2 == 0) tmp >>= 1, max_base++;
        root = 2;
        while(root.power(root,(mod - 1) >> 1) == 1) root += 1;
        dw.resize(max_base);
        idw.resize(max_base);
        for(int i = 0; i < max_base; i++) {
            dw[i] = -root.power(root,(mod - 1) >> (i + 2));
            idw[i] = mint(1) / dw[i];
        }
    }

    void ntt(vector< mint > &a) {
        const int n = (int) a.size();
        assert((n & (n - 1)) == 0);
        assert(__builtin_ctz(n) <= max_base);
        for(int m = n; m >>= 1;) {
            mint w = 1;
            for(int s = 0, k = 0; s < n; s += 2 * m) {
                for(int i = s, j = s + m; i < s + m; ++i, ++j) {
                    auto x = a[i], y = a[j] * w;
                    a[i] = x + y, a[j] = x - y;
                }
                w *= dw[__builtin_ctz(++k)];
            }
        }
    }

    void intt(vector<mint> &a, bool f = true) {
        const int n = (int) a.size();
        assert((n & (n - 1)) == 0);
        assert(__builtin_ctz(n) <= max_base);
        for(int m = 1; m < n; m *= 2) {
            mint w = 1;
            for(int s = 0, k = 0; s < n; s += 2 * m) {
                for(int i = s, j = s + m; i < s + m; ++i, ++j) {
                    auto x = a[i], y = a[j];
                    a[i] = x + y, a[j] = (x - y) * w;
                }
                w *= idw[__builtin_ctz(++k)];
            }
        }
        if(f) {
            mint inv_sz = mint(1) / n;
            for(int i = 0; i < n; i++) a[i] *= inv_sz;
        }
    }

    vector<mint> multiply(vector<mint> a, vector<mint> b) {
        int need = a.size() + b.size() - 1;
        int nbase = 1;
        while((1 << nbase) < need) nbase++;
        int sz = 1 << nbase;
        a.resize(sz, 0);
        b.resize(sz, 0);
        ntt(a);
        ntt(b);
        mint inv_sz = mint(1) / sz;
        for(int i = 0; i < sz; i++) a[i] *= b[i] * inv_sz;
        intt(a, false);
        a.resize(need);
        return a;
    }
};

int32_t main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    int n,m; cin>>n>>m;

    std::vector<mint>a(n), b(m); 
    for(auto &x : a) cin>>x;
    for(auto &x : b) cin>>x;

    NTT<mint>ntt;
    auto c = ntt.multiply(a,b);
    for(int i = 0;i<sz(c);i++) cout<<c[i]<<" ";

    return 0;

}