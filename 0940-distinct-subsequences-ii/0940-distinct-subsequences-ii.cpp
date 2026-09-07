class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        vector<long long> dp(s.size() + 1, 0);
        vector<int> last(26, 0);

        dp[0] = 1;  // empty subsequence

        for (int i = 1; i <= s.size(); i++) {
            int c = s[i - 1] - 'a';

            dp[i] = (2 * dp[i - 1]) % MOD;

            if (last[c] != 0) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }

            last[c] = i;
        }

        // Remove empty subsequence
        return (dp[s.size()] - 1 + MOD) % MOD;
    }
};