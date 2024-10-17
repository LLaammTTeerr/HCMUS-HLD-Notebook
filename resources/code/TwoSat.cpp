#include <bits/stdc++.h>

class TwoSat {
private:
	int n, no;
	int* comp;
	bool* was;
	std::vector <int>* g;
	std::vector <int>* g_t;
	std::vector <int> topo;

	void add_edge(int u, int v) {
		g[u].push_back(v);
		g_t[v].push_back(u);
	}

	void dfs_topo(int u) {
		was[u] = 1;
		for (int v : g[u])
			if (not was[v])
				dfs_topo(v);
		topo.push_back(u);
	}

	void dfs_scc(int u) {
		for (int v : g_t[u]) if (not comp[v]) {
			comp[v] = comp[u];
			dfs_scc(v);
		}
	}
public:
	TwoSat(int _n = 0) : n(_n), no(0) {
		topo.reserve(2 * n);
		comp = new int [2 * n + 1];
		g = new std::vector <int> [2 * n + 1];
		g_t = new std::vector <int> [2 * n + 1];
		was = new bool [2 * n + 1];

		comp += n;
		g += n;
		g_t += n;
		was += n;
	}

	void add_disjunction(int u, int v) {
		add_edge(-u, v);
		add_edge(-v, u);
	}

	std::vector <int>* solve(void) {
		for (int i = 1; i <= n; i += 1) {
			if (not was[i])
				dfs_topo(i);
			if (not was[-i])
				dfs_topo(-i);
		}
		std::reverse(topo.begin(), topo.end());
		for (int u : topo) {
			if (not comp[u]) {
				comp[u] = ++no;
				dfs_scc(u);
			}
		}
		std::vector <int>* ans = new std::vector <int> (n + 1);
		for (int i = 1; i <= n; i += 1) {
			int x = comp[i], y = comp[-i];
			if (x == y)
				return nullptr;
			(*ans)[i] = x > y;
		}
		return ans;
	}
};

int main(void) {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(nullptr);

	int n, m; std::cin >> m >> n;
	TwoSat ts(n);
	while (m--) {
		int u, v; std::cin >> u >> v;
		ts.add_disjunction(u, v);
	}
	std::vector <int>* ans = ts.solve();
	if (ans == nullptr) {
		std::cout << "NO\n";
	} else {
		std::cout << "YES\n";
		int k = std::count(ans->begin(), ans->end(), 1);
		std::cout << k << '\n';
		for (int i = 1; i <= n; i += 1) if (ans->at(i))
			std::cout << i << ' ';
	}

	return 0^0;
}