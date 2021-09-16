#include "bits/stdc++.h"
#define int long long

using namespace std;

/*struct to find the bridge tree of a graph*/
struct BridgeEdge{
    int u, v, index, weight;
    BridgeEdge(int u, int v, int index, int weight): u(u), v(v), index(index), weight(weight) {}
};

struct Graph{

    struct edge{
        int child, index, weight;
        edge(int child, int index, int weight) : child(child), index(index), weight(weight) {}
    };    

    int n, m;

    /*follows 1-based indexing of edges and nodes*/
    std::vector<std::vector<edge>>adj;
    std::vector<bool> isBridge;

    Graph(int _n, int _m){
        n = _n, m = _m;
        adj.resize(n + 1);
        isBridge.resize(m + 1);
    }

    void addEdge(int node, int child, int index, int weight){
        adj[node].push_back(edge(child, index, weight));
    }

    void dfs(int node, int par, std::vector<bool> &visited, std::vector<int> &discTime, std::vector<int> &lowTime, std::vector<BridgeEdge> &bridges, int &timer){
        visited[node] = true;
        discTime[node] = lowTime[node] = timer++;
        for(auto &e : adj[node]){
            if(e.child == par) continue;
            if(visited[e.child]){
                lowTime[node] = min(lowTime[node], discTime[e.child]);
            }
            else{
                dfs(e.child, node, visited, discTime, lowTime, bridges, timer);
                lowTime[node] = min(lowTime[node], lowTime[e.child]);
                if(lowTime[e.child] > discTime[node]){
                    bridges.push_back(BridgeEdge(node, e.child, e.index, e.weight));
                }
            }
        }
    }

    std::vector<BridgeEdge> findBridges(){
        std::vector<BridgeEdge> bridges;
        std::vector<bool> visited(n + 1, false);
        std::vector<int> discTime(n + 1, 0), lowTime(n + 1, 0);
        int timer = 0;
        dfs(1, 0, visited, discTime, lowTime, bridges, timer);
        for(auto &e : bridges){
            isBridge[e.index] = true;
        }
        return bridges;
    }

    void mergeNodes(int node, int par, int compId, std::vector<bool> &visited, std::vector<int> &componentId){
        visited[node] = true;
        componentId[node] = compId;
        for(auto &e : adj[node]){
            if(e.child == par) continue;
            if(!visited[e.child] && !isBridge[e.index]){
                mergeNodes(e.child, node, compId, visited, componentId);
            }
        }
    }

    /*constructed bridge tree will have 1-based indexing*/
    /*returns numOfNodes in bridge tree and adj list of the tree */
    pair<int,std::vector<std::vector<int>>> bridgeTree(std::vector<BridgeEdge> &bridges){
        std::vector<bool>visited(n + 1, false);
        std::vector<int> componentId(n + 1);
        int compId = 1;
        for(int i = 1;i<=n;i++){
            if(!visited[i]){
                mergeNodes(i, 0, compId, visited, componentId);
                compId++;
            }
        }
        std::vector<std::vector<int>> tree(compId + 1);
        for(auto &e : bridges){
            int u = e.u, v = e.v;
            u = componentId[u], v = componentId[v];
            if(u == v) continue;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        return make_pair(compId - 1, tree);
    }
};

int32_t main(){

    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m; cin>>n>>m;
    Graph G(n, m);
    
    for(int i = 1;i<=m;i++){
        int u, v; cin>>u>>v;
        G.addEdge(u, v, i, 0);
        G.addEdge(v, u, i, 0);
    }

    std::vector<BridgeEdge> bridges = G.findBridges();
    auto BridgeTree = G.bridgeTree(bridges);

    int totalBriges = BridgeTree.first - 1;
    std::vector<std::vector<int>> adj = BridgeTree.second;

    return 0;

}
