int strictlyIncreasingLIS(std::vector<int> &v, int n){
    multiset<int>m;
    for(int x : v){
        m.insert(x);
        auto it = m.lower_bound(x);
        it++;
        if(it != m.end()) m.erase(it);
    }
    return int(m.size());
}

int LIS(std::vector<int> &v, int n){
    multiset<int>m;
    for(int x : v){
        m.insert(x);
        auto it = m.upper_bound(x);
        if(it != m.end()) m.erase(it);
    }
    return int(m.size());
}

