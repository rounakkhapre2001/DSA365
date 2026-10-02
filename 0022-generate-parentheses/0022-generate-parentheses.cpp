class Solution {
public:
    vector<string> ans;

    void backtrack(string cur, int open, int close, int n) {
        // We have used all n pairs
        if (cur.size() == 2 * n) {
            ans.push_back(cur);
            return;
        }

        // Add '(' if we still have some left
        if (open < n) {
            backtrack(cur + "(", open + 1, close, n);
        }

        // Add ')' only when it won't make the sequence invalid
        if (close < open) {
            backtrack(cur + ")", open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack("", 0, 0, n);
        return ans;
    }
};