class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 2; // Any subarray of length 2 satisfies a * b == gcd(a, b) * lcm(a, b)

        for (int i = 0; i < n; ++i) {
            long long prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; ++j) {
                prod *= nums[j];
                if (prod > 25200) {
                    break;
                }
                g = std::gcd(g, (long long)nums[j]);
                l = std::lcm(l, (long long)nums[j]);

                if (prod == l * g) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};