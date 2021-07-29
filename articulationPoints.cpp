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

#warning check mod carefully
using mint = modnum<mod>;

const int NN = 202;
class matrix{
public:
    mint mat[NN][NN];
    int r, c;
    matrix(){
        for(int i = 0;i<=NN-1;i++)
            for(int j = 0;j<=NN-1;j++)
                mat[i][j] = 0;
    }
    void setsize(int _r, int _c){ r = _r, c = _c; }
    inline matrix operator * (const matrix &a){
        assert(c == a.r);
        matrix temp;
        temp.setsize(r, a.c);
        for(int i = 0;i<=r-1;i++)
            for(int j = 0;j<=a.c-1;j++){
                for(int k = 0;k<=a.r-1;k++){
                    temp.mat[i][j] += (mat[i][k] * a.mat[k][j]);
                }
            }
        return temp;
    }
    inline matrix operator + (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        for(int i = 0;i<=r-1;i++)
            for(int j = 0;j<=c-1;j++){
                temp.mat[i][j] = mat[i][j] + a.mat[i][j] ;
            }
        return temp;
    }
    inline matrix operator - (const matrix &a){
        assert(r == a.r && c == a.c);
        matrix temp;
        temp.setsize(r, c);
        for(int i = 0;i<=r-1;i++)
            for(int j = 0;j<=c-1;j++){
                temp.mat[i][j] = mat[i][j] - a.mat[i][j];
            }
        return temp;
    }
    inline void operator = (const matrix &a){
        for(int i = 0;i<=r-1;i++)
            for(int j = 0;j<=c-1;j++)
                mat[i][j] = a.mat[i][j];
        r = a.r, c = a.c;
    }
    inline void print(){
        for(int i = 0;i<=r-1;i++){
            for(int j = 0;j<=c-1;j++)
                cout << mat[i][j] << " ";
            cout << endl;
        }
    }
};
matrix pow(matrix a,int k){
    assert(a.r == a.c);
    matrix ans;
    for(int i = 0;i<=a.r-1;i++)
        ans.mat[i][i] = 1;
    ans.r = a.r;
    ans.c = a.r;
    while(k){
        if(k & 1)
            ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}