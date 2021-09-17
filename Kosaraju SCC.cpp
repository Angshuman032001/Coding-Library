#include "bits/stdc++.h"

using namespace std;

void dfs(int node, std::vector<std::vector<int>> &adj, stack<int> &st, std::vector<bool> &visited){
    visited[node] = true;
    for(int child : adj[node]){
        if(!visited[child]) dfs(child, adj, st, visited);
    }
    st.push(node);
}

void reverseDfs(int node, std::vector<std::vector<int>> &transpose, std::vector<bool> &visited){
    cout<<node<<" ";
    visited[node] = true;
    for(int child : transpose[node]){
        if(!visited[child]){
            reverseDfs(child, transpose, visited);
        }
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;
    std::vector<std::vector<int>> adj(n + 1);
    std::vector<bool> visited(n + 1, false);
    for(int i = 1;i<=m;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
    }

    stack<int>st;

    for(int i = 1;i<=n;i++){
        if(!visited[i]){
            dfs(i, adj, st, visited);
        }
    }

    std::vector<std::vector<int>> transpose(n + 1);
    for(int i = 1;i<=n;i++){
        visited[i] = false;
        for(int child : adj[i]){
            transpose[child].push_back(i);
        }
    }

    for(int i = 1;i<=n;i++){
        int node = st.top();
        st.pop();
        if(!visited[node]){
            cout<<"SCC: ";
            reverseDfs(node, transpose, visited);
            cout<<"\n";
        }
    }

}
