int root, n;
vector<int> g[N];
int nBase = 0, nChain = 0;
int head[N], ind[N], basePos[N], par[N], cnt[N];
 
namespace HLD {
    void hld(int u) {
        if(head[nChain] == 0) head[nChain] = u;
        ind[u] = nChain;
 
        basePos[u] = ++nBase;
 
        int mx = -1;
 
        for(int v : g[u]) {
            if (v == par[u]) continue;
            if (mx == -1 || cnt[v] > cnt[mx]) mx = v;
        }
 
        if(mx > -1) {
            hld(mx);
         
            for(int v : g[u]) {
                if(v == par[u]) continue;
                if(v != mx) {
                    nChain++;
                    hld(v);
                }
            }
        }
    }
 
    void dfs(int u) {
        cnt[u] = 1;
        for(int v : g[u]) {
            if(v == par[u]) continue;
            par[v] = u;
            dfs(v);
            cnt[u] += cnt[v];
        }
    }
 
    void update(int u, int v, int val) {
        while(true) {
            int uchain = ind[u], vchain = ind[v];
            if (uchain == vchain) {
 
                int st = basePos[u], en = basePos[v];
                if(st > en) swap(st, en);
                
                // ST.update(1, 1, n, st, en, val);
                break;
            }
 
            if (uchain < vchain) {
                swap(u, v);
                swap(uchain, vchain);   
            }
 
            int st = basePos[head[uchain]], en = basePos[u];
            if(st > en) swap(st, en);
            
            // ST.update(1, 1, n, st, en, val);
 
            u = par[head[uchain]];
            uchain = ind[u];
        }
    }
}