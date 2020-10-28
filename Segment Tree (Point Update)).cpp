//Credits : invictus_123, kactl, bqi343

//Zero - indexing
template <class T> struct SegTree {
    const T ID = 0; //default value
    int n; vector <T> seg;
    T comb(T a, T b) { return (a + b); } //any associative function
    SegTree(int _n) { n = _n; seg.assign(4 * n, ID); }
    void _update(int i, int st, int en, int idx, T val) {
        if(st == en) {
            seg[i] = val;
            return;
        }
        int mid = (st + en) / 2;
        if(mid < idx) _update(2 * i + 1, mid + 1, en, idx, val);
        else _update(2 * i, st, mid, idx, val);
        seg[i] = comb(seg[2 * i], seg[2 * i + 1]);
    }
    T _query(int i, int st, int en, int l, int r) {
        if(en < l || r < st) return ID;
        if(l <= st && en <= r) return seg[i];
        int mid = (st + en) / 2;
        return comb(_query(2 * i, st, mid, l, r), _query(2 * i + 1, mid + 1, en, l, r));
    }
    T query(int l, int r) { return _query(1, 0, n - 1, l, r); }
    void update(int idx, T val) { _update(1, 0, n - 1, idx, val); }
    int _kthOne(int i, int st, int en, int k){
        if(st == en) return st;
        int mid = (st + en)/2;
        if(seg[2*i] >= k) return _kthOne(2*i, st, mid, k);
        else return _kthOne(2*i+1,mid+1,en,k-seg[2*i]);
    }
    int kthOne(int k){
        return _kthOne(1,0,n-1,k);
    }
};
