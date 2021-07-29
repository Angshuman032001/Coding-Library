#include "bits/stdc++.h"

using namespace std;

int timer = 0, cc = 0;
std::vector<std::vector<int>> adj;
std::vector<int> tin, low;
std::vector<bool> onStack, visited;
std::vector<int> ccNum;
stack<int>st;

void init(int n){
    adj = std::vector<std::vector<int>>(n + 1);
    tin.resize(n + 1, 0), low.resize(n + 1, 0);
    onStack.resize(n + 1, false), visited.resize(n + 1, false);
    ccNum.resize(n + 1, -1);
    timer = 0, cc = 0;
}

void tarjan(int node, int par = -1){
    visited[node] = true;
    tin[node] = low[node] = timer++;
    st.push(node);
    onStack[node] = true;
    for(int child : adj[node]){
        if(child == par) continue;
        if(!visited[child]){
            tarjan(child, node);
            low[node] = min(low[node], low[child]);
        }
        else if(onStack[child]){
            low[node] = min(low[node], low[child]);
        }
    }
    if(tin[node] == low[node]){
        cc++;
        while(st.top() != node){
            ccNum[st.top()] = cc;
            onStack[st.top()] = false;
            st.pop();
        }
        onStack[node] = false;
        ccNum[node] = cc;
        st.pop();
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;
    init(n);
    int cc = 0;

    for(int i = 1;i<=m;i++){
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
    }

    for(int i = 1;i<=n;i++){
        if(!visited[i]){
            tarjan(i);
        }
    }

    map<int,int>ccFreq;
    for(int i = 1;i<=n;i++){
        int ccNumOfNode = ccNum[i];
        ccFreq[ccNumOfNode]++;
    }

    for(int i = 1;i<=n;i++){
        int ccNumOfNode = ccNum[i];
        cout<<i<<" : "<<ccNumOfNode<<"\n";
    }
    return 0;
}