inline ll hilbertOrder(ll x, ll y, ll pow, ll rotate)
{
    if (pow == 0) {
        return 0;
    }
    ll hpow = 1 << (pow-1);
    ll seg = (x < hpow) ? (
                           (y < hpow) ? 0 : 3
                           ) : (
                                (y < hpow) ? 1 : 2
                                );
    seg = (seg + rotate) & 3;
    const ll rotateDelta[4] = {3, 0, 0, 1};
    ll nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    ll nrot = (rotate + rotateDelta[seg]) & 3;
    ll subSquareSize = 1ll << (2*pow - 2);
    ll ans = seg * subSquareSize;
    ll add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query
{
    ll l, r,idx;
    ll ord;
    inline void calcOrder() {
        ord = hilbertOrder(l, r, 21, 0);
    }
};

inline bool operator<(const Query &a,const Query &b){
    return a.ord<b.ord;
}



// Arpa's Mo sorting algorithm
// S = the max integer number which is less than sqrt(N);
bool cmp(Query A, Query B){
    if (A.l / S != B.l / S) return A.l < B.l;
    return A.l / S % 2 ? A.r > B.r : A.r < B.r;
}
// Code Example in main 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<Query> q(n);
    for(int i=0;i<n;i++){
        q[i].l=dis[i+1];
        q[i].r=dis[i+1]+sz[i+1]-1;
        q[i].idx=i+1;
        q[i].calcOrder();
    }
    sort(all(q));
    int l=1,r=n;
    map<ll,ll> mt;
    for(int i=1;i<=n;i++){
        mt[v[temp[i]]]++;
    }
    for(int i=0;i<n;i++){
        while(l>q[i].l){
            mt[v[temp[l-1]]]++;
            l--;
        }
        while(r<q[i].r){
            mt[v[temp[r+1]]]++;
            r++;
        }
        while(l<q[i].l){
            if(mt[v[temp[l]]]==1){
                mt.erase(v[temp[l]]);
            }
            else{
                mt[v[temp[l]]]--;
            }
            l++;
        }
        while(r>q[i].r){
            if(mt[v[temp[r]]]==1){
                mt.erase(v[temp[r]]);
            }
            else{
                mt[v[temp[r]]]--;
            }
            r--;
        }
        ans[q[i].idx]=(int)mt.size();
    }
}
