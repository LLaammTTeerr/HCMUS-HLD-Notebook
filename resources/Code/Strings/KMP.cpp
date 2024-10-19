void kmp(const string &str) { // 1-indexed
    int strLen(sz(str) - 1);
    lps[1] = 0;
    for (int i = 2; i <= strLen; ++i) {
        int k = lps[i - 1];
        while(k > 0 && str[k + 1] != str[i]) k = lps[k];
        lps[i] = k + (str[k + 1] == str[i]);
    }
}
