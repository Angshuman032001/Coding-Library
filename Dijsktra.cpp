vi dist;

void init(int n){
    dist.resize(n+1,inf);
}

void dijsktra(int src){
    dist[src] = 0;
    priority_queue<pair<int,int> >q;
    q.push({0,src});
    while (!q.empty()) {
        int a = q.top().second; 
        q.pop();
        if (visited[a]) continue;
        visited[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (dist[a]+w < dist[b]) {
                dist[b] = dist[a]+w;
                q.push({-dist[b],b});
            }
        }
    }
}
