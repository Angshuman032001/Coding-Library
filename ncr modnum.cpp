
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

template<typename T, typename U> mint power(T a, U  b) {
    mint res = 1, x=a; while(b>0){ if(b&1) res *= x; x=(x*x); b>>=1;} return res;
}

/*import modnum first*/

std::vector<mint> fact(N), invfact(N);

void precompute(){
    fact[0] = fact[1] = 1;
    for(int i = 2;i<N;i++) fact[i] = i*fact[i-1];
    invfact[N-1] = fact[N-1].inv();
    for(int i = N-2;i>=0;i--) invfact[i] = invfact[i+1]*(i+1);
}
 
mint nCr(int x, int y){
    if(y > x) return 0;
    mint num = fact[x];
    num *= invfact[y];
    num *= invfact[x-y];
    return num;
}
