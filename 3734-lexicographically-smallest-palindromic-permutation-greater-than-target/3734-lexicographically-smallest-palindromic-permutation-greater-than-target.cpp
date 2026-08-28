class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int cnt[26] = {0};
        for (char ch : s) cnt[ch - 'a']++;
        
        int oddCount = 0, midChar = -1;
        for (int c = 0; c < 26; c++) {
            if (cnt[c] % 2 == 1) { oddCount++; midChar = c; }
        }
        if (n % 2 == 0) { if (oddCount != 0) return ""; }
        else { if (oddCount != 1) return ""; }
        
        int avail[26];
        for (int c = 0; c < 26; c++) avail[c] = cnt[c] / 2;
        int half = n / 2;
        string targetHalf = target.substr(0, half);
        
        vector<array<int,26>> snap(half + 1);
        for (int c = 0; c < 26; c++) snap[0][c] = avail[c];
        
        int matchLen = 0;
        int bestI = -1;
        
        for (int i = 0; i < half; i++) {
            int t = targetHalf[i] - 'a';
            // check breakpoint feasibility at position i
            for (int c = t + 1; c < 26; c++) {
                if (snap[i][c] > 0) { bestI = i; break; }
            }
            if (snap[i][t] > 0) {
                snap[i+1] = snap[i];
                snap[i+1][t]--;
                matchLen = i + 1;
            } else {
                break;
            }
        }
        
        // Try exact match case
        if (matchLen == half) {
            string h = targetHalf;
            string second = h;
            reverse(second.begin(), second.end());
            string S = h;
            if (midChar != -1) S += char('a' + midChar);
            S += second;
            if (S > target) return S;
        }
        
        // Try smallest h > targetHalf
        if (bestI != -1) {
            array<int,26> rem = snap[bestI];
            int t0 = targetHalf[bestI] - 'a';
            int chosen = -1;
            for (int c = t0 + 1; c < 26; c++) {
                if (rem[c] > 0) { chosen = c; break; }
            }
            rem[chosen]--;
            
            string h = targetHalf.substr(0, bestI);
            h += char('a' + chosen);
            for (int c = 0; c < 26; c++) {
                for (int k = 0; k < rem[c]; k++) h += char('a' + c);
            }
            
            string second = h;
            reverse(second.begin(), second.end());
            string S = h;
            if (midChar != -1) S += char('a' + midChar);
            S += second;
            return S;
        }
        
        return "";
    }
};