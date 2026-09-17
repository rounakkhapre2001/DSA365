class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // best[i] = minimum length of a valid subarray
        // completely within [0...i]
        vector<int> best(n, INF);

        int left = 0;
        long long sum = 0;
        int ans = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window if sum becomes greater than target
            while (sum > target) {
                sum -= arr[left++];
            }

            // If current window has target sum
            if (sum == target) {
                int len = right - left + 1;

                // Need a previous non-overlapping subarray
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, len + best[left - 1]);
                }

                // Store the shortest valid subarray found so far
                if (right == 0)
                    best[right] = len;
                else
                    best[right] = min(best[right - 1], len);
            }
            else {
                // Carry forward previous best
                if (right > 0)
                    best[right] = best[right - 1];
            }
        }

        return ans == INF ? -1 : ans;
    }
};