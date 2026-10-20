
class Solution {
public:
    bool canSortBlock(vector<int>& nums, int start, int k) {
        int descents = 0;

        for (int i = 0; i < k - 1; i++) {
            if (nums[start + i] > nums[start + i + 1]) {
                descents++;
            }
        }

        if (descents == 0) return true;
        if (descents > 1) return false;

        // A single descent permits a cyclic rotation,
        // but the rotated block must be checked globally.
        return nums[start + k - 1] <= nums[start];
    }

    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            if (k == 1) {
                if (is_sorted(nums.begin(), nums.end())) {
                    ans++;
                }
                continue;
            }

            vector<int> result;
            bool valid = true;

            for (int start = 0; start < n; start += k) {
                int descents = 0;
                int drop = -1;

                for (int j = start; j < start + k - 1; j++) {
                    if (nums[j] > nums[j + 1]) {
                        descents++;
                        drop = j;
                    }
                }

                if (descents > 1) {
                    valid = false;
                    break;
                }

                int rotationStart = (descents == 1)
                    ? drop + 1
                    : start;

                for (int j = 0; j < k; j++) {
                    result.push_back(
                        nums[start + (rotationStart - start + j) % k]
                    );
                }
            }

            if (valid && is_sorted(result.begin(), result.end())) {
                ans += k;
            }
        }

        return ans;
    }
};
