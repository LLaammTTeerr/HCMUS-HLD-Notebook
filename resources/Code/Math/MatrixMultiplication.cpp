template <class T>
struct Matrix {
	int n, m;
	vector <vector <T>> self;

	Matrix(int _n = 0, int _m = 0, bool unit = false) : n(_n), m(_m) {
		self.assign(n, vector <T> (m + 1, 0));
		if (unit)
			for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
				self[i][j] = i == j;
	}

	Matrix(const vector <vector <T>>& value) {
		n = value.size();
		m = n ? value.begin()->size() : 0;
		self = value;
	}

	Matrix(initializer_list <initializer_list <T>> value) {
		n = value.size();
		m = n ? value.begin()->size() : 0;
		self.reserve(n);
		self.insert(self.end(), value.begin(), value.end());
	}

	auto& operator [] (int i) { assert(i < n); return self[i]; }
	const auto& operator [] (int i) const { assert(i < n); return self[i]; }

	Matrix operator + (const Matrix& other) const {
		assert(n == other.n and m == other.m);
		Matrix ans(n, m);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
			ans[i][j] = (*this)[i][j] + other[i][j];
		return ans;
	}

	Matrix operator - (const Matrix& other) const {
		assert(n == other.n and m == other.m);
		Matrix ans(n, m);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
			ans[i][j] = (*this)[i][j] - other[i][j];
		return ans;
	}

	Matrix operator - (void) const {
		Matrix ans(n, m);
		for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
			ans[i][j] = -(*this)[i][j];
		return ans;
	}

	Matrix operator * (const Matrix& other) const {
		assert(m == other.n);
		Matrix ans(n, other.m);
		for (int i = 0; i < n; i++) for (int j = 0; j < other.m; j++) for (int k = 0; k < m; k++)
			ans[i][j] += (*this)[i][k] * other[k][j];
		return ans;
	}

	inline Matrix& operator += (const Matrix& other) { return *this = (*this) + other; }
	inline Matrix& operator -= (const Matrix& other) { return *this = (*this) - other; }
	inline Matrix& operator *= (const Matrix& other) { return *this = (*this) * other; }
	inline bool operator == (const Matrix& other) const { return self == other.self; }
	inline bool operator != (const Matrix& other) const { return not (self == other.self); }

	template <class U>
	friend ostream& operator << (ostream& cout, const Matrix <U>& lhs) {
		for (int i = 0; i < lhs.n; i++) for (int j = 0; j < lhs.m; j++)
			cout << lhs[i][j] << " \n"[j + 1 == lhs.m];
		return cout;
	}
};