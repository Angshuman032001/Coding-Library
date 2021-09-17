struct UF{

    std::vector<int> parent;
    std::vector<int> size;

    void init(int n){
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x){
        return x == parent[x] ? x : (parent[x] = find(parent[x]));
    }

    bool sameSet(int a, int b){
        return find(a) == find(b);
    }

    int getSize(int x){
        return size[find(x)];
    }

    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(size[a] < size[b]){
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

};
