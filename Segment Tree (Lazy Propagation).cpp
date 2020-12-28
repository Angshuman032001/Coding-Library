int arr[N];

template<class T>struct SegmentTreeLazy{
    int n, N;
    std::vector<T>tree,lazy;

    /*unit is for query and NOP is for updates*/

    const int NOP = 0; //change according to problem
    const int unit = inf;//change according to problem
    
    void init(int _n){
        n = _n;
        N = 4*_n;
        tree.resize(N);
        lazy.resize(N);
    }

    //change operation carefully
    void operation(int &a, int b){
        if(b != NOP) a = a + b;
    }

    //change merge carefully
    int merge(int a, int b){
        return min(a, b);
    }

    void propagate(int i, int l, int r){
        //cant propagte from leaf node
        if(l != r){
            operation(tree[2*i],lazy[i]);
            operation(tree[2*i+1],lazy[i]);
            operation(lazy[2*i],lazy[i]);
            operation(lazy[2*i+1],lazy[i]);
            lazy[i]=NOP;
        }
    }

    void _update(int i, int l, int r, int rx, int ry, int val){
        propagate(i,l,r);
        if(rx<=l and r<=ry){
            operation(tree[i],val);
            operation(lazy[i],val);
            return;
        }
        else if(r<rx or l>ry) return;
        else{
            int mid = l + (r - l)/2;
            _update(2*i, l, mid, rx, ry, val);
            _update(2*i+1, mid+1, r, rx, ry, val);
            tree[i] = merge(tree[2*i],tree[2*i+1]);
        }
    }

    T _query(int i, int l, int r, int rx, int ry){
        propagate(i,l,r);
        if(rx<=l and r<=ry) return tree[i];
        else if(r<rx || l>ry) return unit;//change unit according to problem
        else{
            int m = l+(r-l)/2;
            return merge(_query(2*i, l, m, rx, ry), _query(2*i+1, m+1, r, rx, ry));
        }
    }

    T query(int l, int r){ return _query(1, 1, n, l, r); }
    void update(int l, int r, T val){ _update(1, 1, n, l, r, val); }

};

SegmentTreeLazy<int>seg;

