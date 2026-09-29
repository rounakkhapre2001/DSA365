class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int len = m + n - 1;

        // Valid parentheses string must have even length
        if (len % 2 == 1)
            return false;

        // dp[i][j] contains all possible balances at (i, j)
        vector<vector<bitset<201>>> dp(m, vector<bitset<201>>(n));

        // First character must be '('
        if (grid[0][0] == ')')
            return false;

        dp[0][0][1] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                int remaining = (m - 1 - i) + (n - 1 - j);

                // Get states from top and left
                bitset<201> prev;

                if (i > 0)
                    prev |= dp[i - 1][j];

                if (j > 0)
                    prev |= dp[i][j - 1];

                if (grid[i][j] == '(') {
                    // balance -> balance + 1
                    dp[i][j] = prev << 1;
                } 
                else {
                    // balance -> balance - 1
                    dp[i][j] = prev >> 1;
                }

                // We cannot have negative balance.
                // Also, balance must be <= remaining cells,
                // otherwise we cannot return to zero.
                for (int balance = remaining + 1; balance <= 200; balance++)
                    dp[i][j][balance] = 0;
            }
        }

        return dp[m - 1][n - 1][0];
    }
};