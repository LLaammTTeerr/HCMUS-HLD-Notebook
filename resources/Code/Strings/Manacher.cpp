int N;
string S;
int pod[MaxN], pev[MaxN];

void calc_pod() {
    int L = 1, R = 0;
    for(int i = 1; i <= N; i++) {
        if(i > R) pod[i] = 0;
        else pod[i] = min(R - i, pod[L + (R - i)]);
        while(i - pod[i] - 1 > 0 && i + pod[i] + 1 <= N && S[i - pod[i] - 1] == S[i + pod[i] + 1]) {
            pod[i]++;
        }

        if(i + pod[i] > R) {
            R = i + pod[i];
            L = i - pod[i];
        }
    }
}

void calc_pev() {
    int L = 1, R = 0;
    for(int i = 1; i < N; i++) {
        int j = i + 1;
        if(j > R) pev[i] = 0;
        else pev[i] = min(R - j + 1, pev[L + (R - j)]);
        while(i - pev[i] > 0 && j + pev[i] <= N && S[i - pev[i]] == S[j + pev[i]]) {
            pev[i]++;
        }
        if(i + pev[i] > R) {
            R = i + pev[i];
            L = j - pev[i];
        }
    }
}

// N = S.length();
// S = ' ' + S;
// calc_pod();
// calc_pev();