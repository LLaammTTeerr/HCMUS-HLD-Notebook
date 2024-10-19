const int N = 50003;
vector<int> adj[N];
int dist[N], matx[N], maty[N], m, n, p;
bool vi[N];

// use Fast Matching
bool bfs(void) {
    queue<int> qu;
    for (int i = 1; i <= m; ++i)
        if(!matx[i]) { dist[i] = 0; qu.push(i); } else { dist[i] = 1e9+7; }
    dist[0] = 1e9+7;
    while(!qu.empty()) {
        int u(qu.front()); qu.pop();
        if(dist[u] < dist[0]) {
            for (int &v : adj[u]) {
                if(dist[maty[v]] >= 1e9+7) {
                    dist[maty[v]] = dist[u] + 1; qu.push(maty[v]);
                }
            }
        }
    }
    return (dist[0] < 1e9+7);
}

bool dfs(const int &u) {
    if(!u) return true;
    for (int &v : adj[u]) {
        if(dist[maty[v]] == dist[u] + 1) {
            if(dfs(maty[v])) {
                matx[u] = v, maty[v] = u;
                return true;
            }
        }
    }
    dist[u] = 1e9+7;
    return false;
}

void process() {
    cin >> m >> n >> p;
    for (int i = 0; i < p; ++i) {
        int u, v; cin >> u >> v; adj[u].push_back(v);
    }
    int res(0);
    while(bfs())
        for (int i = 1; i <= m; ++i) if(!matx[i]) res += dfs(i);
}