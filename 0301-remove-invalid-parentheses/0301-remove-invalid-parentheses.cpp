#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        helper(s, 0, 0, '(', ')', ans);
        return ans;
    }

private:
    void helper(string s, int last_i, int last_j,
                char open, char close,
                vector<string>& ans) {

        int count = 0;

        for (int i = last_i; i < s.size(); i++) {

            if (s[i] == open)
                count++;
            else if (s[i] == close)
                count--;

            // Invalid: extra closing parenthesis
            if (count < 0) {

                // Try removing one ')' from this range
                for (int j = last_j; j <= i; j++) {

                    // Avoid removing duplicate consecutive ')'
                    if (s[j] == close &&
                        (j == last_j || s[j - 1] != close)) {

                        string t = s.substr(0, j) +
                                   s.substr(j + 1);

                        helper(t, i, j, open, close, ans);
                    }
                }

                return;
            }
        }

        // No extra ')' found.
        // Reverse and check for extra '('.
        string reversed = s;
        reverse(reversed.begin(), reversed.end());

        if (open == '(') {
            helper(reversed, 0, 0, ')', '(', ans);
        } 
        else {
            ans.push_back(reversed);
        }
    }
};