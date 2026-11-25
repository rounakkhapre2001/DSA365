class Solution {
    struct State {
        int len = 0;
        int link = -1;
        int cnt = 0;
        map<int, int> next;
    };

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<State> st;
        st.reserve(2 * n);
        st.push_back(State{}); // root state 0
        int last = 0;

        for (int x : nums) {
            int cur = st.size();
            st.push_back(State{st[last].len + 1, 0, 1, {}});
            int p = last;

            while (p != -1 && !st[p].next.count(x)) {
                st[p].next[x] = cur;
                p = st[p].link;
            }

            if (p != -1) {
                int q = st[p].next[x];
                if (st[p].len + 1 == st[q].len) {
                    st[cur].link = q;
                } else {
                    int clone = st.size();
                    st.push_back(State{st[p].len + 1, st[q].link, 0, st[q].next});
                    while (p != -1 && st[p].next[x] == q) {
                        st[p].next[x] = clone;
                        p = st[p].link;
                    }
                    st[q].link = st[cur].link = clone;
                }
            }
            last = cur;
        }

        // Counting sort states by length to propagate occurrence counts bottom-up
        int m = st.size();
        vector<int> bucket(n + 1, 0), order(m);
        for (int i = 0; i < m; ++i) bucket[st[i].len]++;
        for (int i = 1; i <= n; ++i) bucket[i] += bucket[i - 1];
        for (int i = m - 1; i >= 0; --i) order[--bucket[st[i].len]] = i;

        for (int i = m - 1; i > 0; --i) {
            int u = order[i];
            st[st[u].link].cnt += st[u].cnt;
        }

        int ans = n;
        for (int u = 1; u < m; ++u) {
            if (st[u].cnt == 1) {
                ans = min(ans, st[st[u].link].len + 1);
            }
        }

        return ans;
    }
};