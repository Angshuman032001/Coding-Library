#include "bits/stdc++.h"
using namespace std;

int timer = 0;

void dfs(int node, int par, int lvl, vector<vector<int>> &adj, vector<int> &level, vector<int> &tin, vector<int> &tout){
    level[node] = lvl;
    tin[node] = timer++;
    for(auto child : adj[node]){
        if(child != par){
            dfs(child, node, lvl + 1, adj, level, tin, tout);
        }
    }
    tout[node] = timer++;
}

bool isAncestor(int a, int b, vector<int> &tin, vector<int> &tout){
    return (tin[a] > tin[b] && tout[a] < tout[b]);
}

int getDistance(int a, int b, vector<int> &level){
    return level[a] - level[b];
}

void solve(){
    int n; cin>>n;
    vector<vector<int>>adj(n + 1);
    for(int i = 1;i<=n;i++){
        int par; cin>>par;
        adj[par].push_back(i);
        adj[i].push_back(par);
    }
    vector<int>level(n + 1, 0), tin(n + 1, 0), tout(n + 1, 0);
    timer = 0;
    dfs(0, -1, 0, adj, level, tin, tout);
    int q; cin>>q;
    while(q--){
        int x, y;  cin>>x>>y;
        if(!isAncestor(x, y, tin, tout)) cout<<"-1\n";
        else cout<<getDistance(x, y, level)<<"\n";
    }
}

int main(){
    int t; cin>>t;
    while(t--){
        solve();
    }
}
