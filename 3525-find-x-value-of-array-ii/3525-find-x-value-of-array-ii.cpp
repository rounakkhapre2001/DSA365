class Solution {
public:
    struct Node {
        int prod;
        int pref[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                pref[i] = 0;
        }
    };

    int n, K;
    vector<Node> seg;

    Node mergeNode(const Node& L, const Node& R) {
        Node res;

        // Product of the complete segment
        res.prod = (L.prod * R.prod) % K;

        // Prefixes completely inside L
        for (int r = 0; r < K; r++) {
            res.pref[r] += L.pref[r];
        }

        // Prefixes = all of L + a prefix of R
        for (int r = 0; r < K; r++) {
            int newRem = (L.prod * r) % K;
            res.pref[newRem] += R.pref[r];
        }

        return res;
    }

    void build(int idx, int l, int r, vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % K;

            seg[idx].prod = rem;
            seg[idx].pref[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, nums);
        build(idx * 2 + 1, mid + 1, r, nums);

        seg[idx] = mergeNode(seg[idx * 2], seg[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, int value) {
        if (l == r) {
            int rem = value % K;

            seg[idx] = Node();
            seg[idx].prod = rem;
            seg[idx].pref[rem] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, value);
        else
            update(idx * 2 + 1, mid + 1, r, pos, value);

        seg[idx] = mergeNode(seg[idx * 2], seg[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        // Completely inside
        if (ql <= l && r <= qr) {
            return seg[idx];
        }

        int mid = (l + r) / 2;

        // Completely in right
        if (qr <= mid) {
            return query(idx * 2, l, mid, ql, qr);
        }

        // Completely in left
        if (ql > mid) {
            return query(idx * 2 + 1, mid + 1, r, ql, qr);
        }

        // Split across both sides
        Node L = query(idx * 2, l, mid, ql, qr);
        Node R = query(idx * 2 + 1, mid + 1, r, ql, qr);

        return mergeNode(L, R);
    }

    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->n = nums.size();
        this->K = k;

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent point update
            update(1, 0, n - 1, index, value);

            // We need prefixes of nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};