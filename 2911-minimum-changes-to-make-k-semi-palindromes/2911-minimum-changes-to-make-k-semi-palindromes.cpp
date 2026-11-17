class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // cost[i][j] = minimum changes to make s[i...j]
        // a semi-palindrome.
        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                // d must be a proper divisor of the substring length.
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    // Compare symmetric characters in each group.
                    for (int offset = 0; offset < d; offset++) {
                        int left = i + offset;
                        int right = j - ((len - 1 - offset) % d);

                        while (left < right) {
                            if (s[left] != s[right])
                                changes++;

                            left += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // dp[p][i] = minimum changes to partition
        // first i characters into p substrings.
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;

        for (int p = 1; p <= k; p++) {
            for (int i = 2 * p; i <= n; i++) {
                for (int j = 2 * (p - 1); j <= i - 2; j++) {
                    if (dp[p - 1][j] == INF) continue;

                    dp[p][i] = min(
                        dp[p][i],
                        dp[p - 1][j] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};