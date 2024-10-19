using T = long double;
const T pi = acos(-1);
using cplx = complex <T>;

void fft(vector <cplx>& a, bool invert) {
	int n = a.size();

	if (n == 1)
		return;

	vector <cplx> a0(n / 2), a1(n / 2);
	for (int i = 0; i < n; i += 1) {
		if (i & 1)
			a1[i / 2] = a[i];
		else
			a0[i / 2] = a[i];
	}

	fft(a0, invert);
	fft(a1, invert);

	T alpha = 2 * pi / n * (invert ? -1 : +1);
	cplx zeta = cplx(cos(alpha), sin(alpha));
	cplx now = 1;

	for (int i = 0; i * 2 < n; i += 1) {
		a[i] = a0[i] + now * a1[i];
		a[i + n / 2] = a0[i] - now * a1[i];

		if (invert) {
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}

		now *= zeta;
	}
}

vector <int> mul_fft(const vector <int>& a, const vector <int>& b) {
	int n = max(a.size(), b.size());

	vector <cplx> ca(a.begin(), a.end()), cb(b.begin(), b.end());

	int lgx = 0;
	while ((1 << lgx) < n)
		lgx += 1;

	ca.resize(1 << lgx);
	cb.resize(1 << lgx);

	n = 1 << lgx;

	fft(ca, false);
	fft(cb, false);

	for (int i = 0; i < n; i += 1)
		ca[i] *= cb[i];

	fft(ca, true);
	vector <int> res(n);

	for (int i = 0; i < n; i += 1)
		res[i] = round(ca[i].real());

	return res;
}