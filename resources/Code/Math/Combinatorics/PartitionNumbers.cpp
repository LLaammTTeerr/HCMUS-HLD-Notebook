// ways of writing n as a sum of positive integers
long long partitionNumber(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1; // Base case: There's 1 way to partition 0

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            // Pentagonal number part
            int pent1 = i - k * (3 * k - 1) / 2;
            int pent2 = i - k * (3 * k + 1) / 2;
            
            // Recurrence relation using pentagonal numbers
            if (pent1 >= 0) dp[i] += (k % 2 == 1) ? dp[pent1] : -dp[pent1];
            if (pent2 >= 0) dp[i] += (k % 2 == 1) ? dp[pent2] : -dp[pent2];
        }
    }
    return dp[n];
}