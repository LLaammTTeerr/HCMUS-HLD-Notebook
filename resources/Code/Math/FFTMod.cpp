typedef complex<double> C;
typedef long double ld;
void fft(vector<C> &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<ld>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (int k = 2; k < n; k *= 2) {
		R.resize(n), rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (int i = k; i < 2 * k; ++i)
            rt[i] = R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
	}
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (int i = 0; i < n; ++i)
        if(i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; ++j) {
				// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  ///
				// include-line
				auto x = (double*) &rt[j + k], y = (double*) &a[i + j + k];  /// exclude-line
				C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
				a[i + j + k] = a[i + j] - z; a[i + j] += z;
			}
		}
	}
}

template<ll MOD> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	vector<ll> res(sz(a) + sz(b) - 1, 0);
	int B = 32 - __builtin_clz(sz(res));
	int n = 1 << B, cut = ll(sqrt(MOD));
	vector<C> L(n), R(n), outs(n), outl(n);
	for (int i = 0; i < sz(a); ++i) L[i] = C(ll(a[i] / cut), ll(a[i] % cut));
	for (int i = 0; i < sz(b); ++i) R[i] = C(ll(b[i] / cut), ll(b[i] % cut));
	fft(L), fft(R);
	for (int i = 0; i < n; ++i) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / C(1.0i);
	}
	fft(outl), fft(outs);
	for (int i = 0; i < sz(res); ++i) {
		ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
		ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
		res[i] = ((av * cut % MOD + bv) * cut % MOD + cv) % MOD;
	}
	return res;
}

void mul(int a[], int b[], ll c[]) {
    vector<ll> pa, pb;
    for (int i = 0; i < k; ++i) {
        pa.push_back(a[i]); pb.push_back(b[i]);
    }
    vector<ll> res = convMod<MOD>(pa, pb);
    for (int i = 0; i < sz(res); ++i) c[i] = res[i];
}