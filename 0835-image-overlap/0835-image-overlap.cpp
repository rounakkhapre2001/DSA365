class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int, int>> ones1, ones2;

        // Store coordinates of 1s in img1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1)
                    ones1.push_back({i, j});
            }
        }

        // Store coordinates of 1s in img2
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img2[i][j] == 1)
                    ones2.push_back({i, j});
            }
        }

        // Count how many pairs have the same translation
        map<pair<int, int>, int> freq;

        int ans = 0;

        for (auto p1 : ones1) {
            for (auto p2 : ones2) {
                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;

                freq[{dx, dy}]++;

                ans = max(ans, freq[{dx, dy}]);
            }
        }

        return ans;
    }
};