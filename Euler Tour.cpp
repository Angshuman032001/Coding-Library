const int mxn = 1e5+10;

std::vector<int> g[mxn];
int inTime[mxn], outTime[mxn], ETT[2*mxn];
int timer = 0;

void dfs(int node , int par){
	inTime[node] = timer;
	ETT[timer] = node;
	timer++;

	for(int child : g[node])
	if(child != par)
	dfs(child , node);
	
	outTime[node] = timer;
	ETT[timer] = node;
	timer++;
}
