int a[N];
//1-based indexing
template <class T> struct SegTree {
    int n; vector <T> tree;
    const T unit = 0; //default value

    T merge(T a, T b) { return (a + b); } //any associative function

    SegTree(int _n) { n = _n; tree.assign(4 * n, unit); }

    void _update(int i, int l, int r, int idx, T val) {
        if(l == r) {
            tree[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if(mid < idx) _update(2 * i + 1, mid + 1, r, idx, val);
        else _update(2 * i, l, mid, idx, val);
        tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    void build(int i, int l, int r){
        if(l == r){
            tree[i] = a[l];
            return;
        }
        int mid = (l + r)/2;
        build(2*i, l, mid);
        build(2*i+1,mid + 1, r);
        tree[i] = merge(tree[2*i],tree[2*i+1]);
    }

    T _query(int i, int l, int r, int rx, int ry) {
        if(r < rx || ry < l) return unit;
        if(rx <= l && r <= ry) return tree[i];
        int mid = (l + r) / 2;
        return merge(_query(2 * i, l, mid, rx, ry), _query(2 * i + 1, mid + 1, r, rx, ry));
    }

    T query(int l, int r) { return _query(1, 1, n, l, r); }

    void update(int idx, T val) { _update(1, 1, n, idx, val); }

    int _kthOne(int i, int l, int r, int k){
        if(l == r) return l;
        int mid = (l + r)/2;
        if(tree[2*i] >= k) return _kthOne(2*i, l, mid, k);
        else return _kthOne(2*i+1,mid+1,r,k-tree[2*i]);
    }
    
    int kthOne(int k){
        return _kthOne(1,0,n-1,k);
    }
};

