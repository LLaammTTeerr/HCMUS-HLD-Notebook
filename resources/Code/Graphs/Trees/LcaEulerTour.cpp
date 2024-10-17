namespace LCA {
    int pos;
    int eu[N << 1];
    int h[N], fa[N], dp[N << 1][20];

    void dfs(int u, int p) {
        h[u] = h[p] + 1;
        eu[++pos] = u;
        fa[u] = pos;

        for(int v : g[u]) {
            if(v == p) continue;
            dfs(v, u);
            eu[++pos] = u;
        }
    }

    void init() {
        pos = 0;
        dfs(1, 0);

        for(int i = 1; i <= pos; i++) dp[i][0] = i;
        for(int j = 1; (1 << j) <= pos; j++) {
            for(int i = 1; i + (1 << j) - 1 <= pos; i++) {
                if(h[eu[dp[i][j - 1]]] < h[eu[dp[i + (1 << (j - 1))][j - 1]]])
                    dp[i][j] = dp[i][j - 1];
                else
                    dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int get(int u, int v) {
        u = fa[u], v = fa[v];
        if(u > v) swap(u, v);
        int k = log2(v - u + 1);

        int ans = eu[dp[u][k]];
        if(h[eu[dp[u][k]]] > h[eu[dp[v - (1 << k) + 1][k]]]) 
            ans = eu[dp[v - (1 << k) + 1][k]];
        
        return ans;
    }
}