class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count[10] = {};

        // Frequency of each digit
        for (int d : digits) {
            count[d]++;
        }

        int ans = 0;

        // Check every 3-digit number
        for (int num = 100; num <= 999; num++) {
            
            // Must be even
            if (num % 2 != 0)
                continue;

            int x = num;

            int ones = x % 10;
            x /= 10;

            int tens = x % 10;
            x /= 10;

            int hundreds = x;

            // Check if required digits are available
            int need[10] = {};
            need[hundreds]++;
            need[tens]++;
            need[ones]++;

            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > count[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};