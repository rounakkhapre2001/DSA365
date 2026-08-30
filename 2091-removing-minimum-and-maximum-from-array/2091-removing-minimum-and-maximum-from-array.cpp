class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        
        int minIdx = 0, maxIdx = 0;
        
        // Find indices of minimum and maximum elements
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIdx])
                minIdx = i;
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }
        
        int left = min(minIdx, maxIdx);
        int right = max(minIdx, maxIdx);
        
        // Case 1: Remove both from the front
        int front = right + 1;
        
        // Case 2: Remove both from the back
        int back = n - left;
        
        // Case 3: Remove one from front and one from back
        int mixed = (left + 1) + (n - right);
        
        return min({front, back, mixed});
    }
};