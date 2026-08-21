class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        // Count distinct amounts <= x
        auto countAmounts = [&](long long x) {
            long long total = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long lcm = 1;
                int bits = 0;
                bool valid = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        long long g = std::gcd(lcm, (long long)coins[i]);

                        // lcm(a,b) = a/gcd(a,b)*b
                        lcm = lcm / g * coins[i];

                        if (lcm > x) {
                            valid = false;
                            break;
                        }
                    }
                }

                if (!valid)
                    continue;

                long long cnt = x / lcm;

                if (bits & 1)
                    total += cnt;
                else
                    total -= cnt;
            }

            return total;
        };

        // Binary search for answer
        long long low = 1;
        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (countAmounts(mid) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};