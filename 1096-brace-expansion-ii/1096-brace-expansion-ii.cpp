class Solution {
public:
    string s;
    int pos = 0;

    // Parse an expression until ',' or '}'
    set<string> parseExpression() {
        set<string> result;
        result.insert("");

        while (pos < s.size() && s[pos] != '}' && s[pos] != ',') {
            set<string> cur;

            if (s[pos] == '{') {
                pos++; // skip '{'
                cur = parseUnion();
                pos++; // skip '}'
            } 
            else {
                cur.insert(string(1, s[pos]));
                pos++;
            }

            // Concatenate result with cur
            set<string> next;

            for (const string& a : result) {
                for (const string& b : cur) {
                    next.insert(a + b);
                }
            }

            result = next;
        }

        return result;
    }

    // Parse comma-separated expressions
    set<string> parseUnion() {
        set<string> result;

        while (true) {
            set<string> cur = parseExpression();

            result.insert(cur.begin(), cur.end());

            if (pos >= s.size() || s[pos] == '}')
                break;

            // s[pos] == ','
            pos++;
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        pos = 0;

        set<string> result = parseUnion();

        return vector<string>(result.begin(), result.end());
    }
};