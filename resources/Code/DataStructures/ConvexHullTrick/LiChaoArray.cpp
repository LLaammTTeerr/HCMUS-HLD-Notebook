template <int MAX>
class LiChao {
private:
	struct Line {
		lli A, B;

		Line(lli A = 0, lli B = 0): A(A), B(B) { }
		inline lli operator () (lli X) const { return A * X + B; }
	} st[4 * MAX + 7];

	void add_line(int id, int l, int r, const Line &vars) {
		if (l > r) return;
		Line cur = st[id], L = vars;

		if (cur(l) < L(l)) swap(cur, L);
		if (cur(r) >= L(r)) st[id] = L;
		else {
			int mid = (l + r) >> 1;
			if (cur(mid) > L(mid)) st[id] = L, add_line(id << 1 | 1, mid + 1, r, cur);
			else st[id] = cur, add_line(id << 1, l, mid, L);
		}
	}

	lli query(int id, int l, int r, lli X) const {
		if (l > r || X < l || X > r) return LINF;

		lli res = st[id] (X);
		if (l == r) return res;

		int mid = (l + r) >> 1;
		res = min(res, query(id << 1, l, mid, X));
		res = min(res, query(id << 1 | 1, mid + 1, r, X));

		return res;
	}
public:
	LiChao(void) { }

	void add_line(lli A, lli B) { add_line(1, 0, MAX, Line(A, B)); }
	lli query(lli X) const { return query(1, 0, MAX, X); }
};