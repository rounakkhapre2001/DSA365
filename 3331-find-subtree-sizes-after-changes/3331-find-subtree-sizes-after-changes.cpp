class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> lastSeen(26, -1);

        auto dfs = [&](auto& self, int u) -> void {
            int c = s[u] - 'a';
            int newParent = (lastSeen[c] != -1) ? lastSeen[c] : parent[u];

            int prev = lastSeen[c];
            lastSeen[c] = u;

            for (int v : adj[u]) {
                self(self, v);
            }

            // Backtrack so sibling subtrees don't see this node
            lastSeen[c] = prev;

            if (newParent != -1) {
                ans[newParent] += ans[u];
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};