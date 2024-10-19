int g[N][N];
int res;
ll edges[N];

void BronKerbosch(int n, ll R, ll P, ll X) { // O(3 ^ (n / 3))
    // here we will find all possible maximal cliques (not maximum) i.e. there is no node which can be included in this set
    if (P == 0ll && X == 0ll) { 
        int t = __builtin_popcountll(R);
        res = max(res, t);
        return;
    }

    int u = 0;
    while (!((1LL << u) & (P | X))) u++;
    for (int v = 0; v < n; v++) {
        if (((1LL << v) & P) && !((1LL << v) & edges[u])) {
            BronKerbosch(n, R | (1LL << v), P & edges[v], X & edges[v]);
            P -= (1LL << v);
            X |= (1LL << v);
        }
    }
}

int max_clique (int n) {
    res = 0;
    for (int i = 1; i <= n; i++) {
        edges[i - 1] = 0;
        for (int j = 1; j <= n; j++)  if (g[i][j]) edges[i - 1] |= (1ll << (j - 1));
    }
    BronKerbosch(n, 0, (1ll << n) - 1, 0);
    return res;
}