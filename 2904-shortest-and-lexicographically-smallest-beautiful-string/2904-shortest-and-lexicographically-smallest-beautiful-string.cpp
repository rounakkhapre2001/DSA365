class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;

        string ans = "";

        for (int right = 0; right < n; right++) {

            if (s[right] == '1')
                ones++;

            // More than k ones -> shrink
            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            // Exactly k ones
            if (ones == k) {

                // Remove leading zeroes
                while (left <= right && s[left] == '0')
                    left++;

                string cur = s.substr(left, right - left + 1);

                // First valid answer OR
                // shorter OR same length but lexicographically smaller
                if (ans.empty() ||
                    cur.length() < ans.length() ||
                    (cur.length() == ans.length() && cur < ans)) {
                    ans = cur;
                }
            }
        }

        return ans;
    }
};