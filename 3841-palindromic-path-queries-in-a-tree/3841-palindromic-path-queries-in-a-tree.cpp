class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n), sz(n), heavy(n, -1);
        vector<int> head(n), pos(n);
        int timer = 0;

        function<void(int,int)> dfs1 = [&](int u, int p) {
            parent[u] = p;
            sz[u] = 1;
            int best = 0;

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs1(v, u);
                sz[u] += sz[v];

                if (sz[v] > best) {
                    best = sz[v];
                    heavy[u] = v;
                }
            }
        };

        function<void(int,int)> dfs2 = [&](int u, int h) {
            head[u] = h;
            pos[u] = timer++;

            if (heavy[u] != -1)
                dfs2(heavy[u], h);

            for (int v : adj[u]) {
                if (v == parent[u] || v == heavy[u]) continue;
                dfs2(v, v);
            }
        };

        dfs1(0, -1);
        dfs2(0, 0);

        vector<int> bit(n + 1, 0);

        auto add = [&](int idx, int val) {
            for (++idx; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto prefix = [&](int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        auto rangeQuery = [&](int l, int r) {
            if (l > r) return 0;
            return prefix(r) ^ (l ? prefix(l - 1) : 0);
        };

        for (int i = 0; i < n; ++i)
            add(pos[i], 1 << (s[i] - 'a'));

        auto pathQuery = [&](int u, int v) {
            int mask = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]])
                    swap(u, v);

                mask ^= rangeQuery(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v])
                swap(u, v);

            mask ^= rangeQuery(pos[u], pos[v]);
            return mask;
        };

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                add(pos[u], 1 << (s[u] - 'a'));
                s[u] = c;
                add(pos[u], 1 << (s[u] - 'a'));
            } else {
                int v;
                ss >> v;

                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};