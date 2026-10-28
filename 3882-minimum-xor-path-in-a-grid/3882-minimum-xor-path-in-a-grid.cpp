
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bool>> dp(m, vector<bool>(n, false));
        vector<vector<unordered_set<int>>> vals(
            m, vector<unordered_set<int>>(n)
        );

        vals[0][0].insert(grid[0][0]);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                if (i > 0) {
                    for (int x : vals[i - 1][j]) {
                        vals[i][j].insert(x ^ grid[i][j]);
                    }
                }

                if (j > 0) {
                    for (int x : vals[i][j - 1]) {
                        vals[i][j].insert(x ^ grid[i][j]);
                    }
                }
            }
        }

        int ans = INT_MAX;
        for (int x : vals[m - 1][n - 1]) {
            ans = min(ans, x);
        }

        return ans;
    }
};
