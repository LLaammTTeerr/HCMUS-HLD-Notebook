struct DSU{
	int par[N], res;
	int d[N];
	vector<pair<int&, int>> history;
	
	void init(){
		res = 1;
		For(i, 1, n) par[i] = -1, d[i] = 0;
	}
	
	void rollBack(int t){
		while ((int)history.size() > t){
			history.back().fi = history.back().se;
			history.pop_back();
		}
	}
	
	void Union(int u, int v){
		
		int du = 0, dv = 0;
		
		while (par[u] > 0) du ^= d[u], u = par[u];
		while (par[v] > 0) dv ^= d[v], v = par[v];
		
		if (u == v){
			res &= du ^ dv;
			return;
		}
		
		if (par[u] > par[v]) swap(u, v);
		
		history.pb({par[u], par[u]});
		history.pb({par[v], par[v]});
		
		par[u] += par[v];
		par[v] = u;
		
		d[v] = du ^ dv ^ 1;
	}
} dsu;