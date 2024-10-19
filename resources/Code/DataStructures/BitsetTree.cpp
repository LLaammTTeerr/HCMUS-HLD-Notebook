struct BitsetTree {
    static const int LAYER = 3;
    static const int BLOCK = 64;

    ull a[MAXN + 100];
    int layer_start[LAYER];

    void update(int x) {
        int id(x >> 6), prev(layer_start[LAYER - 1] + id);
        a[prev] ^= (1ULL << (x & (BLOCK - 1)));
        for (int i = LAYER - 2; i >= 0; --i) {
            x >>= 6, id >>= 6;
            int digit(x & (BLOCK - 1)), cur(layer_start[i] + id);
            if((a[prev] > 0) != (a[cur] >> digit & 1)) a[cur] ^= 1ULL << digit;
            prev = cur;
        }
    }

    inline int findR(ull mask, int i) {
        ull x(-1); mask &= (x << i);
        if(i >= BLOCK || mask == 0) return -1;
        return __builtin_ctzll(mask);
    }

    int walk_forward(int x) {
        int id(x >> 6), pos = findR(a[layer_start[LAYER - 1] + id], x & (BLOCK - 1));
        if(pos != -1) return x - (x & (BLOCK - 1)) + pos;
        for (int i = LAYER - 2; i >= 0; --i) {
            id >>= 6, x >>= 6;
            int cur(layer_start[i] + id), digit = (x & (BLOCK - 1)) + 1;
            int pos = findR(a[cur], digit);
            if(pos != -1) {
                id = (id << 6) + pos;
                for (int j = i + 1; j < LAYER; ++j) {
                    int digit = __builtin_ctzll(a[layer_start[j] + id]);
                    id = (id << 6) + digit;
                }
                return id;
            }
        }
        return -1;
    }

    int findL(ull mask, int i) {
        mask &= (1ULL << i) - 1;
        if(i >= BLOCK || mask == 0) return -1;
        return 63 - __builtin_clzll(mask);
    }

    int walk_backward(int x) {
        int id(x >> 6), pos = findL(a[layer_start[LAYER - 1] + id], x & (BLOCK - 1));
        if(pos != -1) return x - (x & (BLOCK - 1)) + pos;
        for (int i = LAYER - 2; i >= 0; --i) {
            id >>= 6, x >>= 6;
            int cur(layer_start[i] + id), digit = (x & (BLOCK - 1));
            int pos = findL(a[cur], digit);
            if(pos != -1) {
                id = (id << 6) + pos;
                for (int j = i + 1; j < LAYER; ++j) {
                    int digit = 63 - __builtin_clzll(a[layer_start[j] + id]);
                    id = (id << 6) + digit;
                }
                return id;
            }
        }
        return -1;
    }

    void init(void) {
        memset(a, 0, sizeof(a));
        int cur(0), sum(1);
        for (int i = 0; i < LAYER; ++i) {
            layer_start[i] = cur; cur += sum; sum *= BLOCK;
        }
    }
} bst;