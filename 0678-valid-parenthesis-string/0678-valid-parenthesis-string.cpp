class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char ch : s) {
            if (ch == '(') {
                low++;
                high++;
            }
            else if (ch == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' acts as ')'
                high++;  // '*' acts as '('
            }

            // Even the maximum possible opens became negative
            if (high < 0)
                return false;

            // We cannot have negative minimum opens
            low = max(low, 0);
        }

        // Valid only if we can end with exactly 0 unmatched '('
        return low == 0;
    }
};