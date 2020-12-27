//credits : invictus_123
const int MAX = 3e5 + 10;
int n, a[MAX];
template <class T> struct SparseTable {
    int n, logn;
    vector <int> log; vector <vector <T>> dp1,dp2;
    SparseTable(int _n) {
        n = _n; logn = ceil(log2(n)) + 1;
        log.assign(n + 1, 0); 
        dp1.assign(logn, vector <T> (n, 0));
        dp2.assign(logn, vector <T> (n, 0));
    }
    T comb1(T a, T b) { return min(a, b); }
    T comb2(T a, T b) { return max(a, b); }
    void build() {
        log[1] = 0;
        for(int i = 0; i <= n; i ++) {
            if(i > 1) log[i] = log[i / 2] + 1;
            if(i < n){
                dp1[0][i] = a[i];
                dp2[0][i] = a[i];
            }
        }
        for(int j = 1; j < logn; j ++) {
            for(int i = 0; i + (1 << j) <= n; i ++) {
                dp1[j][i] = comb1(dp1[j - 1][i], dp1[j - 1][i + (1 << (j - 1))]);
                dp2[j][i] = comb2(dp2[j - 1][i], dp2[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T query1(int l, int r) {
        int ln = log[r - l + 1];
        return comb1(dp1[ln][l], dp1[ln][r - (1 << ln) + 1]);
    }
    T query2(int l, int r) {
        int ln = log[r - l + 1];
        return comb2(dp2[ln][l], dp2[ln][r - (1 << ln) + 1]);
    }
};
