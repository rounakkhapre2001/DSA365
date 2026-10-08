class Solution {
public:
    int lengthLongestPath(string input) {
        unordered_map<int, int> path;
        path[0] = 0;
        
        int ans = 0;
        int level = 0;
        
        for (int i = 0; i < input.size();) {
            int depth = 0;
            
            while (i < input.size() && input[i] == '\t') {
                depth++;
                i++;
            }
            
            int start = i;
            while (i < input.size() && input[i] != '\n') {
                i++;
            }
            
            string name = input.substr(start, i - start);
            
            if (name.find('.') != string::npos) {
                ans = max(ans, path[depth] + (int)name.size());
            } else {
                path[depth + 1] = path[depth] + name.size() + 1;
            }
            
            if (i < input.size() && input[i] == '\n')
                i++;
        }
        
        return ans;
    }
};