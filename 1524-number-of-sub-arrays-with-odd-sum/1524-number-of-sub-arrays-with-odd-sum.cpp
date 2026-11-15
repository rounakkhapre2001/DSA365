class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;

        long long even = 1, odd = 0;
        long long ans = 0;
        int prefix = 0;

        for (int num : arr) {
            prefix = (prefix + num) % 2;

            if (prefix == 1) {
                ans = (ans + even) % MOD;
                odd++;
            } else {
                ans = (ans + odd) % MOD;
                even++;
            }
        }

        return ans;
    }
};