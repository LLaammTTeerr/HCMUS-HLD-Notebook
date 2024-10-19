pli factor(ll n) {
    int s = __builtin_ctz(n);
    return make_pair(n / (1LL << s), s);
}

ll mulmod(ll a, ll expo, ll MOD) {
    ll res = 0;
    while(expo > 0) {
        if(expo & 1) {
            if((res += a) >= MOD)
                res -= MOD;
        }

        expo >>= 1;
        if((a += a) >= MOD)
            a -= MOD;
    }

    return res;
}

ll powermod(ll a, ll expo, ll MOD) {
    ll res = 1;
    while(expo > 0) {
        if(expo & 1)
            res = mulmod(res, a, MOD);

        a = mulmod(a, a, MOD);
        expo >>= 1;
    }

    return res;
}

ll powermod2(ll a, ll expo, ll MOD) {
    ll res = 1;
    while(expo > 0) {
        if(expo & 1)
            res = res * a % MOD;

        a = a * a % MOD;
        expo >>= 1;
    }

    return res;
}

bool test_a(ll s, ll d, ll n, ll a) {
    if(n == a)
        return true;

    ll p = powermod(a, d, n);
    if(p == 1)
        return true;

    for (; s > 0; --s) {
        if(p == n - 1)
            return true;

        p = mulmod(p, p, n);
    }

    return false;
}

bool test_a2(ll s, ll d, ll n, ll a) {
    if(n == a)
        return true;

    ll p = powermod2(a, d, n);
    if(p == 1)
        return true;

    for (; s > 0; --s) {
        if(p == n - 1)
            return true;

        p = p * p % n;
    }

    return false;
}

bool miller(ll n) {
    if(n < 2)
        return false;

    if((n & 1) == 0)
        return (n == 2);

    ll d;
    int s;
    tie(d, s) = factor(n - 1);

    vector<int> test_prime;
    if(n <= 1e9) {
        test_prime = {2, 7, 61};
    } else {
        test_prime = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    }

    for (int i = 0; i < sz(test_prime); ++i) {
        if(n <= 1e9) {
            if(!test_a2(s, d, n, test_prime[i]))
                return false;

            continue;
        }

        if(!test_a(s, d, n, test_prime[i]))
            return false;
    }

    return true;
}