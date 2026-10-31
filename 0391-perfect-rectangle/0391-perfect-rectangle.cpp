class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        long long area = 0;
        int minX = INT_MAX, minY = INT_MAX;
        int maxX = INT_MIN, maxY = INT_MIN;

        set<pair<int, int>> corners;

        for (const auto& r : rectangles) {
            int x1 = r[0], y1 = r[1];
            int x2 = r[2], y2 = r[3];

            minX = min(minX, x1);
            minY = min(minY, y1);
            maxX = max(maxX, x2);
            maxY = max(maxY, y2);

            area += 1LL * (x2 - x1) * (y2 - y1);

            pair<int, int> pts[] = {
                {x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}
            };

            for (auto p : pts) {
                if (corners.count(p))
                    corners.erase(p);
                else
                    corners.insert(p);
            }
        }

        long long boundingArea =
            1LL * (maxX - minX) * (maxY - minY);

        if (area != boundingArea)
            return false;

        set<pair<int, int>> expected = {
            {minX, minY}, {minX, maxY},
            {maxX, minY}, {maxX, maxY}
        };

        return corners == expected;
    }
};