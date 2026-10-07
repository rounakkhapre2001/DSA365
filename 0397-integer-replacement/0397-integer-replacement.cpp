class Solution {
public:
    int integerReplacement(int n) {
        long long x = n;
        int steps = 0;

        while (x != 1) {
            if (x % 2 == 0) {
                x /= 2;
            }
            else {
                // For odd numbers, choose +1 or -1 wisely
                if (x == 3 || (x & 2) == 0)
                    x--;
                else
                    x++;
            }

            steps++;
        }

        return steps;
    }
};