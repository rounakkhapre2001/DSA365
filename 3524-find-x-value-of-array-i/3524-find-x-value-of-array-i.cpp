class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);

        // dp[r] = number of subarrays ending at the
        // previous position with product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> next(k, 0);

            int x = num % k;

            // Start a new subarray: [num]
            next[x]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] == 0)
                    continue;

                int newRemainder = (r * x) % k;

                next[newRemainder] += dp[r];
            }

            // Every subarray ending here contributes to result
            for (int r = 0; r < k; r++) {
                result[r] += next[r];
            }

            dp = next;
        }

        return result;
    }
};