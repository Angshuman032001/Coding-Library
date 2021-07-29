#include "bits/stdc++.h"

using namespace std;

const int N = 1000;

std::vector<int>adj[N], tin(N, 0), low(N, 0);
std::vector<bool> visited(N, false);

set<pair<int,int>>bridges;

int timer = 0;

void dfs(int node, int par = -1){
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for(int child : adj[node]){
        if(child == par) continue;
        if(visited[child]){
            low[node] = min(low[node], tin[child]);
        }
        else{
            dfs(child, node);
            low[node] = min(low[node], low[child]);
            if(low[child] > tin[node]){
                bridges.insert(make_pair(node, child));
            }
        }
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;cin>>n;
    int m; cin>>m;
    for(int i = 1;i<=m;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }  

    dfs(1, -1);

    for(auto x : bridges) cout<<x.first<<" "<<x.second<<"\n";

} 