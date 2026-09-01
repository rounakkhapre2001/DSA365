class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sx, sy;
        int litterCount = 0;
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }
                if (classroom[i][j] == 'L') {
                    litterId[i][j] = litterCount++;
                }
            }
        }

        int fullMask = (1 << litterCount) - 1;

        // State: x, y, collectedMask, remainingEnergy
        // dist stores minimum moves.
        queue<array<int, 4>> q;

        // For each (x, y, mask), keep maximum remaining energy seen.
        // If we reach the same state with less/equal energy, it is useless.
        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(1 << litterCount, -1))
        );

        q.push({sx, sy, 0, energy});
        best[sx][sy][0] = energy;

        int moves = 0;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [x, y, mask, rem] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                // If standing on Reset area, restore energy
                if (classroom[x][y] == 'R')
                    rem = energy;

                // Cannot move with 0 energy
                if (rem == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                        continue;

                    if (classroom[nx][ny] == 'X')
                        continue;

                    int newRem = rem - 1;
                    int newMask = mask;

                    if (classroom[nx][ny] == 'L') {
                        newMask |= (1 << litterId[nx][ny]);
                    }

                    // Reset energy immediately when reaching R
                    if (classroom[nx][ny] == 'R') {
                        newRem = energy;
                    }

                    if (best[nx][ny][newMask] >= newRem)
                        continue;

                    best[nx][ny][newMask] = newRem;
                    q.push({nx, ny, newMask, newRem});
                }
            }

            moves++;
        }

        return -1;
    }
};