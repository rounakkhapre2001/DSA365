class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });
        
        vector<int> result(n);
        int i = 0;
        while (i < n) {
            int j = i;
            // group consecutive (in sorted order) elements whose adjacent diff <= limit
            while (j + 1 < n && nums[idx[j+1]] - nums[idx[j]] <= limit) {
                j++;
            }
            // group is idx[i..j], values sorted (since idx sorted by value)
            vector<int> positions(idx.begin() + i, idx.begin() + j + 1);
            sort(positions.begin(), positions.end());
            for (int k = 0; k < (int)positions.size(); k++) {
                result[positions[k]] = nums[idx[i + k]];
            }
            i = j + 1;
        }
        
        return result;
    }
};