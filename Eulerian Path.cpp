struct DirectedEulerPath {

    int n; 
    vector<vector<int>> adj;
    vector<int> path;

    void init(int _n){
        n = _n;
        adj = vector<vector<int>>(n + 1);
        path.clear();
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
    }

    void dfs(int node){
        while(adj[node].size()){
            int neighbour = adj[node].back();
            adj[node].pop_back();
            dfs(neighbour);
        }
        path.push_back(node);
    }

    bool getPath(){
        int cntEdges = 0;
        vector<int>outdegree(n + 1, 0), indegree(n + 1, 0);
        for(int i = 1;i<=n;i++){
            cntEdges += adj[i].size();
            outdegree[i] += adj[i].size();
            for(auto neighbour : adj[i]) indegree[neighbour]++;
        }
        int cntMiddle = 0, src = 1;
        for(int i = 1;i<=n;i++){
            if(abs(indegree[i] - outdegree[i]) > 1) return false;
            if(indegree[i] == outdegree[i]) cntMiddle++;
            if(outdegree[i] > indegree[i]) src = i;
        }
        if(cntMiddle != n && cntMiddle + 2 != n) return false;
        dfs(src);
        reverse(path.begin(), path.end());
        return (path.size() == cntEdges + 1);
    }
};
