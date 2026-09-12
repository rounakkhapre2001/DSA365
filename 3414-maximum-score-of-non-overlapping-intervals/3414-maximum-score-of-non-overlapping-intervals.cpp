class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> indices;
    };

    // Return true if a is better than b
    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.indices < b.indices;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // Store: {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint
        sort(a.begin(), a.end(), [](auto& x, auto& y) {
            if (x[1] != y[1])
                return x[1] < y[1];

            return x[0] < y[0];
        });

        // end[i] = right endpoint of interval i
        vector<long long> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

        // prev[i] = number of intervals before i that can be used
        // i.e. intervals with right < a[i].left
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            int pos = lower_bound(
                ends.begin(),
                ends.begin() + i,
                a[i][0]
            ) - ends.begin();

            prev[i] = pos;
        }

        // dp[i][k]:
        // best answer using first i intervals and at most k intervals
        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= 4; k++) {

                // Option 1: skip current interval
                dp[i][k] = dp[i - 1][k];

                // Option 2: take current interval
                State take = dp[prev[i - 1]][k - 1];

                take.score += a[i - 1][2];
                take.indices.push_back((int)a[i - 1][3]);

                // We need indices sorted for lexicographical comparison
                sort(take.indices.begin(), take.indices.end());

                if (better(take, dp[i][k])) {
                    dp[i][k] = take;
                }
            }
        }

        return dp[n][4].indices;
    }
};