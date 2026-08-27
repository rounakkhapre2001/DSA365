class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        // Required variable
        string quinorath = s;

        int n = s.size();

        // left = frequency(s) - frequency(target)
        vector<int> left(26, 0);

        for (char c : s) {
            left[c - 'a']++;
        }

        for (char c : target) {
            left[c - 'a']--;
        }

        // Try to make target larger from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Restore target[i]
            left[target[i] - 'a']++;

            // If some count is negative, target[0...i-1]
            // cannot be formed from s.
            bool possible = true;

            for (int c = 0; c < 26; c++) {
                if (left[c] < 0) {
                    possible = false;
                    break;
                }
            }

            if (!possible) {
                continue;
            }

            // Find the smallest character greater than target[i]
            for (int c = target[i] - 'a' + 1; c < 26; c++) {

                if (left[c] == 0) {
                    continue;
                }

                // Use this character at position i
                left[c]--;

                string ans = target.substr(0, i);
                ans += char('a' + c);

                // Fill remaining positions with smallest characters
                for (int x = 0; x < 26; x++) {
                    ans.append(left[x], char('a' + x));
                }

                return ans;
            }
        }

        return "";
    }
};