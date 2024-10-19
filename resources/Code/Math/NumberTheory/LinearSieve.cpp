// calc mobius inversion and number divisor of x with all (x <= n) O(n)
void linearSieve(void) {
    u[1] = 1, numd[1] = 1;
    vector<int> primes;
    for (int i = 2; i < MAXN; ++i) {
        if(!isComp[i]) {
            primes.push_back(i); u[i] = -1;
            numd[i] = 2, cnt[i] = 1;
        }
        for (int j = 0; j < sz(primes) && i * primes[j] < MAXN; ++j) {
            isComp[i * primes[j]] = 1;
            if(i % primes[j] == 0) {
                u[i * primes[j]] = 0;
                numd[i * primes[j]] = numd[i] / (cnt[i] + 1) * (cnt[i] + 2);
                cnt[i * primes[j]] = cnt[i] + 1;
                break;
            } else {
                u[i * primes[j]] = u[i] * u[primes[j]];
                numd[i * primes[j]] = numd[i] * numd[primes[j]];
                cnt[i * primes[j]] = 1;
            }
        }
    }
}