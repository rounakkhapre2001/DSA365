class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans;
        ans.reserve(num.size());

        for (char c : num) {
            while (!ans.empty() && k > 0 && ans.back() > c) {
                ans.pop_back();
                --k;
            }
            ans.push_back(c);
        }

        if (k > 0) {
            ans.resize(max(0, (int)ans.size() - k));
        }

        size_t pos = ans.find_first_not_of('0');
        if (pos == string::npos) {
            return "0";
        }
        return ans.substr(pos);
    }
};