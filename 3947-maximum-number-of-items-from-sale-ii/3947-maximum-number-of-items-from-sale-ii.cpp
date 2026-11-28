class Solution {
    struct Option {
        long long gain;
        long long cost;
        long long count; // -1 means unlimited within budget
    };

public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        for (const auto& it : items) {
            freq[it[0]]++;
        }

        vector<int> multCount(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            for (int m = f; m <= n; m += f) {
                multCount[f] += freq[m];
            }
        }

        vector<Option> opts;
        opts.reserve(2LL * n);

        for (const auto& it : items) {
            long long f = it[0];
            long long price = it[1];
            long long m = multCount[f] - 1; // other items j with f | factor_j

            if (m > 0) {
                opts.push_back({2, price, m});
            }
            opts.push_back({1, price, -1});
        }

        sort(opts.begin(), opts.end(), [](const Option& a, const Option& b) {
            // Compare a.gain / a.cost > b.gain / b.cost without floating-point error
            __int128 lhs = (__int128)a.gain * b.cost;
            __int128 rhs = (__int128)b.gain * a.cost;
            if (lhs != rhs) return lhs > rhs;
            return a.cost < b.cost;
        });

        long long rem = budget;
        long long ans = 0;

        for (const auto& opt : opts) {
            if (rem < opt.cost) continue;
            long long maxByBudget = rem / opt.cost;
            long long take = (opt.count == -1) ? maxByBudget : min(opt.count, maxByBudget);
            ans += take * opt.gain;
            rem -= take * opt.cost;
        }

        return (int)ans;
    }
};