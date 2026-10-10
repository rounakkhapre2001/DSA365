class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<int> diff(n);
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
        }

        long long total = 0;
        for (int d : diff) {
            total += d;
        }

        // If all differences can be reduced to zero
        if (k >= total) {
            return 0;
        }

        // Find the smallest maximum difference we can achieve
        int low = 0, high = maxDiff;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        // Reduce every difference above low to low
        long long ans = 0;
        long long used = 0;

        for (int d : diff) {
            if (d > low) {
                used += d - low;
                d = low;
            }
            ans += 1LL * d * d;
        }

        // Distribute remaining operations to reduce differences
        // from low to low - 1.
        long long remaining = k - used;

        // Each such operation reduces the square by 2*low - 1.
        ans -= remaining * (2LL * low - 1);

        return ans;
    }
};