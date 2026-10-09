class Solution {
public:
    int minInsertions(string s) {
        int ans = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } 
            else {
                // If the next character is ')',
                // use both ')' as one closing pair.
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } 
                else {
                    // Insert one ')' to complete the pair.
                    ans++;
                }

                // If there is no unmatched '(',
                // insert one '('.
                if (open > 0) {
                    open--;
                } 
                else {
                    ans++;
                }
            }
        }

        // Each remaining '(' needs two ')'.
        ans += open * 2;

        return ans;
    }
};