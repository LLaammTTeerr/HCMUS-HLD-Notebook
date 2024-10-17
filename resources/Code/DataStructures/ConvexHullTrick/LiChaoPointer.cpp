const int64_t INF = 1e18 + 7;

struct Line {
	int64_t a, b;

	Line(int64_t a = 0, int64_t b = -INF) : a(a), b(b) {}

	inline int64_t operator () (int64_t x) const { return a * x + b; }
};

//get max over all ax + b with x const
struct LiChao {
	Line value;
	LiChao* lef;
	LiChao* rig;

	LiChao(void) : value(Line()), lef(nullptr), rig(nullptr) {}

	void update(int l, int r, int u, int v, const Line& LINE) {
		if (l > r or u > v or u > r or l > v)
			return;

		if (u <= l and r <= v) {
			Line current = value, other = LINE;
			if (current(l) > other(l))
				swap(current, other);

			if (current(r) <= other(r))
				value = other;
			else {
				if (l == r)
					return;
				int m = (l + r) >> 1;
				if (current(m) > other(m)) {
					value = current;
					lef = lef ? lef : new LiChao();
					lef->update(l, m, u, v, other);
				} else {
					value = other;
					rig = rig ? rig : new LiChao();
					rig->update(m + 1, r, u, v, current);
				}
			}
			return;
		}

		int m = (l + r) >> 1;
		lef = lef ? lef : new LiChao();
		rig = rig ? rig : new LiChao();

		lef->update(l, m, u, v, LINE);
		rig->update(m + 1, r, u, v, LINE);
	}

	int64_t query(int l, int r, int x) {
		if (l > r or x > r or l > x)
			return -INF;
		int64_t ans = value(x);

		int m = (l + r) >> 1;
		ans = max(ans, lef ? lef->query(l, m, x) : -INF);
		ans = max(ans, rig ? rig->query(m + 1, r, x) : -INF);
		return ans;
	}
};
