class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxSum = INT_MIN;

        for (int left = 0; left < cols; ++left) {
            vector<int> rowSum(rows, 0);

            for (int right = left; right < cols; ++right) {
                for (int i = 0; i < rows; ++i) {
                    rowSum[i] += matrix[i][right];
                }

                set<long long> prefixSet;
                prefixSet.insert(0);

                long long currSum = 0;

                for (int sum : rowSum) {
                    currSum += sum;

                    auto it = prefixSet.lower_bound(currSum - k);
                    if (it != prefixSet.end()) {
                        maxSum = max(maxSum,
                                     static_cast<int>(currSum - *it));
                    }

                    prefixSet.insert(currSum);
                }
            }
        }

        return maxSum;
    }
};