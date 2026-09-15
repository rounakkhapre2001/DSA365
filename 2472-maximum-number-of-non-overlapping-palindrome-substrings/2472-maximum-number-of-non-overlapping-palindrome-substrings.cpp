class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // isPal[i][j] = true if s[i...j] is a palindrome
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        // Build palindrome table
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (s[i] == s[j] && (len <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        // dp[i] = maximum number of palindromes
        // using first i characters
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't use a palindrome ending at i-1
            dp[i] = dp[i - 1];

            // Try every palindrome ending at i-1
            for (int l = 0; l < i; l++) {
                int len = i - l;

                if (len >= k && isPal[l][i - 1]) {
                    dp[i] = max(dp[i], dp[l] + 1);
                }
            }
        }

        return dp[n];
    }
};