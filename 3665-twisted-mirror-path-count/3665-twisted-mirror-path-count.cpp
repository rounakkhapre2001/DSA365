class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1'000'000'007;
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                // Try moving right (direction 0).
                int r = i, c = j + 1, dir = 0;

                while (r < m && c < n && grid[r][c] == 1) {
                    if (dir == 0) {
                        ++r;       // Right-entered mirror: move down.
                        dir = 1;
                    } else {
                        ++c;       // Down-entered mirror: move right.
                        dir = 0;
                    }
                }

                if (r < m && c < n)
                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;

                // Try moving down (direction 1).
                r = i + 1;
                c = j;
                dir = 1;

                while (r < m && c < n && grid[r][c] == 1) {
                    if (dir == 0) {
                        ++r;
                        dir = 1;
                    } else {
                        ++c;
                        dir = 0;
                    }
                }

                if (r < m && c < n)
                    dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
            }
        }

        return dp[m - 1][n - 1];
    }
};