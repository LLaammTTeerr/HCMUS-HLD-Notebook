// 1^k + 2^k + ... + p^k (1 <= p <= 1e9, 1 <= k <= 20)
inline ll C2(int n) { return 1LL * n * (n + 1) / 2 % modl; }
inline ll nCk(int n, int k) {
    return (k > n) ? 0 : frac[n] * finv[k] % modl * finv[n - k] % modl; }

ll powermod(ll a, int exponent) {
    ll res(1);
    while(exponent > 0) {
        if(exponent & 1) res = res * a % modl;
        exponent >>= 1; a = a * a % modl;
    }
    return res;
}

ll tmp[22];
ll bernoulli(int n) {
    for (int i = 0; i <= n; ++i) {
        tmp[i] = inv[i + 1];
        for (int j = i; j > 0; --j)
            tmp[j - 1] = 1LL * j * (tmp[j - 1] - tmp[j] + modl) % modl;
    }
    return tmp[0];
}

// calc(n) = sigma(p^k) (1 <= p <= n)
ll calc(int n) {
    ll res(0), invn = powermod(n, modl - 2);
    n = powermod(n, expo + 1);
    for (int k = 0; k <= expo; ++k) {
        res = (res + n * nCk(expo + 1, k) % modl * B[k] % modl) % modl;
        n = n * invn % modl;
    }
    return res * powermod(expo + 1, modl - 2) % modl;
}

void init(void) {
    frac[0] = finv[0] = 1;
    for (int i = 1; i <= 21; ++i) {
        frac[i] = frac[i - 1] * i % modl, finv[i] = powermod(frac[i], modl - 2);
        inv[i] = powermod(i, modl - 2);
    }
    for (int i = 0; i <= 20; ++i) B[i] = bernoulli(i);
}