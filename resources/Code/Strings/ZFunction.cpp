void ZAlgorithm(const string &str) {
    int L(0), R(0), strLen(str.size());
    Z[0] = strLen;
    for (int i = 1; i < strLen; ++i) {
        if(i > R) {
            L = R = i;
            while(R < strLen && str[R] == str[R - L]) ++R;
            Z[i] = R-- - L;
        } else {
            int k(i - L);
            if(Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;
                while(R < strLen && str[R] == str[R - L]) ++R;
                Z[i] = R-- - L;
            }
        }
    }
}