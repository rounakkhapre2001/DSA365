class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int remaining = 0;

        for (int value : data) {
            if (value < 0 || value > 255)
                return false;

            if (remaining == 0) {
                if ((value >> 7) == 0) {
                    remaining = 0;           // 1-byte character
                } else if ((value >> 5) == 0b110) {
                    remaining = 1;           // 2-byte character
                } else if ((value >> 4) == 0b1110) {
                    remaining = 2;           // 3-byte character
                } else if ((value >> 3) == 0b11110) {
                    remaining = 3;           // 4-byte character
                } else {
                    return false;
                }
            } else {
                if ((value >> 6) != 0b10)
                    return false;

                --remaining;
            }
        }

        return remaining == 0;
    }
};