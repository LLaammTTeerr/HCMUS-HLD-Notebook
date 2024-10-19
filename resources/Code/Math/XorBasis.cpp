struct Node {
    int basis[MAXLOG], szBasis;

    Node() {
        szBasis = 0; memset(basis, 0, sizeof(basis));
    }

    void insertVector(int mask) {
        while(mask > 0) {
            int i = __builtin_ctz(mask & -mask);
            if(!basis[i]) {
                basis[i] = mask; ++szBasis;
                return;
            }
            mask ^= basis[i];
        }
    }

    bool checkVector(int mask) {
        while(mask > 0) {
            int i = __builtin_ctz(mask & -mask);
            if(!basis[i]) return false;
            mask ^= basis[i];
        }
        return true;
    }

    Node mergeNode(const Node &a) {
        Node res(*this);
        for (int i = 0; i < MAXLOG; ++i) {
            if(!a.basis[i]) continue;
            res.insertVector(a.basis[i]);
        }
        return res;
    }

    // find k-th biggest element in Basis
    int query(int k) const {
        int mask(0), tot(1 << szBasis);
        for (int i = MAXLOG - 1; i >= 0; --i) {
            if(basis[i]) {
                int low(tot >> 1);
                if(low < k && !(mask >> i & 1) || low >= k && (mask >> i & 1))
                    mask ^= basis[i];
                if(low < k) k -= low;
                tot >>= 1;
            }
        }
        return mask;
    }

    int getMax(void) {
        int res(0);
        for (int i = 0; i < MAXLOG; ++i)
            if(!(res >> i & 1)) res ^= basis[i];
        return res;
    }

};