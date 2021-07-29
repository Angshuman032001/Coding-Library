const int MAXN = 20;

vector<int>adj[N];
bool visited[N];
int parent[N], level[N], LCA[N][MAXN];
 
void dfs(int node, int par, int lvl){
    level[node] = lvl;
    LCA[node][0] = par;
    parent[node] = par;
    for(int child : adj[node]){
        if(child != par) 
            dfs(child, node, lvl + 1);
    }
}
 
void init(int n){
    for(int j = 1;j<MAXN;j++){
        for(int i = 1;i<=n;i++){
            if(LCA[i][j-1] != -1){
                LCA[i][j] = LCA[LCA[i][j-1]][j-1];
            }
        }
    }
}
 
int getLCA(int a , int b){
    if(level[a] > level[b])
    swap(a , b);
    int d = level[b] - level[a];
    int f = 0;
    for(int j = MAXN - 1;j>=0;j--){
        if(d & (1<<j)){
            b = LCA[b][j];
        }
    }
    if(a == b)
    return a;
    for(int j=MAXN-1;j>=0;j--)
        if(LCA[a][j] != -1 && (LCA[a][j] != LCA[b][j]))
        a = LCA[a][j] , b = LCA[b][j];   
    return LCA[a][0];
}