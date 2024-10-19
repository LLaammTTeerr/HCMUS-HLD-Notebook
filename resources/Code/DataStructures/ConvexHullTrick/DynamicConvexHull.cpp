struct Line {
    ll k, m;
    mutable ll p;
    bool operator < (const Line& o) const {
        return k < o.k;
    }
    bool operator < (const ll &x) const {
        return p < x;
    }
};
 
struct DynamicHull : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = LLONG_MAX;
   
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool bad(iterator x, iterator y) {
        if(y == end()) { 
            x->p = inf;
            return false; 
        }

        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);

        return x->p >= y->p;
    }

    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (bad(y, z)) z = erase(z);

        if(x != begin() && bad(--x, y)) bad(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p) bad(x, erase(y));
    }

    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};