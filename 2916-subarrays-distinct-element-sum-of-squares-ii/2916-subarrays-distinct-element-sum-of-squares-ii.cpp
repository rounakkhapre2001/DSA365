
class Solution {
public:
    static const int MOD = 1'000'000'007;
    
    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };
    
    vector<Node> seg;
    int n;
    
    void apply(int node, int l, int r, long long v) {
        long long len = r - l + 1;
        seg[node].sq = (seg[node].sq
            + 2LL * v % MOD * seg[node].sum % MOD
            + len % MOD * v % MOD * v % MOD) % MOD;
        
        seg[node].sum = (seg[node].sum + len % MOD * v) % MOD;
        seg[node].lazy = (seg[node].lazy + v) % MOD;
    }
    
    void push(int node, int l, int r) {
        if (seg[node].lazy == 0 || l == r) return;
        
        int mid = (l + r) / 2;
        apply(node * 2, l, mid, seg[node].lazy);
        apply(node * 2 + 1, mid + 1, r, seg[node].lazy);
        seg[node].lazy = 0;
    }
    
    void update(int node, int l, int r, int ql, int qr, long long v) {
        if (ql > r || qr < l) return;
        
        if (ql <= l && r <= qr) {
            apply(node, l, r, v);
            return;
        }
        
        push(node, l, r);
        int mid = (l + r) / 2;
        
        update(node * 2, l, mid, ql, qr, v);
        update(node * 2 + 1, mid + 1, r, ql, qr, v);
        
        seg[node].sum = (seg[node * 2].sum
                       + seg[node * 2 + 1].sum) % MOD;
        seg[node].sq = (seg[node * 2].sq
                      + seg[node * 2 + 1].sq) % MOD;
    }
    
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        seg.assign(4 * n, Node());
        
        vector<int> last(100001, -1);
        long long ans = 0;
        
        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];
            
            // Add 1 to distinct counts for subarrays
            // ending at i that contain a new occurrence.
            update(1, 0, n - 1, prev + 1, i, 1);
            
            last[nums[i]] = i;
            
            // Sum of squares for all subarrays ending at i.
            ans = (ans + seg[1].sq) % MOD;
        }
        
        return ans;
    }
};
