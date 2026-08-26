class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        // Always binary search on the smaller array
        if (nums1.size() > nums2.size())
            swap(nums1, nums2);

        int n1 = nums1.size();
        int n2 = nums2.size();

        int low = 0;
        int high = n1;

        while (low <= high) {

            int cut1 = low + (high - low) / 2;
            int cut2 = (n1 + n2 + 1) / 2 - cut1;

            // Elements just left of partition
            int left1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int left2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];

            // Elements just right of partition
            int right1 = (cut1 == n1) ? INT_MAX : nums1[cut1];
            int right2 = (cut2 == n2) ? INT_MAX : nums2[cut2];

            // Correct partition
            if (left1 <= right2 && left2 <= right1) {

                // Total length is even
                if ((n1 + n2) % 2 == 0) {
                    int leftMax = max(left1, left2);
                    int rightMin = min(right1, right2);

                    return (leftMax + rightMin) / 2.0;
                }

                // Total length is odd
                else {
                    return max(left1, left2);
                }
            }

            // We took too many elements from nums1
            else if (left1 > right2) {
                high = cut1 - 1;
            }

            // We took too few elements from nums1
            else {
                low = cut1 + 1;
            }
        }

        return 0.0;
    }
};