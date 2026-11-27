class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> bonus(n, 0);
        int minPrice = INT_MAX;

        for (int i = 0; i < n; ++i) {
            minPrice = min(minPrice, items[i][1]);
            for (int j = 0; j < n; ++j) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    ++bonus[i];
                }
            }
        }

        vector<int> dp(budget + 1, 0);
        for (int i = 0; i < n; ++i) {
            int cost = items[i][1];
            int val = 1 + bonus[i];
            for (int w = budget; w >= cost; --w) {
                dp[w] = max(dp[w], dp[w - cost] + val);
            }
        }

        int ans = 0;
        for (int w = 0; w <= budget; ++w) {
            int extra = (budget - w) / minPrice;
            ans = max(ans, dp[w] + extra);
        }

        return ans;
    }
};