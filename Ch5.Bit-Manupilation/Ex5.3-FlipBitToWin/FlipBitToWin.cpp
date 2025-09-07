// Flip Bit to Win: You have an integer and you can flip exactly one bit from a O to a 1. Write code to
// find the length of the longest sequence of 1 s you could create.
// EXAMPLE
// Input:  1775 (or: 11011101111)
// Output: 8

#include <stdio.h>
#include <vector>

unsigned int FlipBitToWin(unsigned int num) {
    if (num == 0U)
        return 1U;
    if (num == ~0U)
        return 32U;
    unsigned int maxLen = 0, curLen = 0, preLen = 0;

    while (num) {
        if (num % 2) {
            curLen++;
        } else {
            preLen = curLen;
            curLen = 0;
        }
        num >>= 1;
        int temp = preLen + 1 + curLen;
        maxLen = (maxLen < temp) ? temp : maxLen;
    }
    return maxLen;
}
int main() {
    std::vector<std::pair<unsigned int, unsigned int>> test = {
        {0b11011101111U, 8},
        {0, 1},
        {0b111111111U, 10},
        {0b1111111110U, 10},
        {0b110111001111U, 6},
        {0b1100111001111U, 5},
        {~0U, 32},
        {((~0U>>2)<<2 | 1U), 32}
    };
    for (int i = 0; i < test.size(); i++) {
        int myOut = FlipBitToWin(test[i].first);
        if (myOut == test[i].second) {
            printf("Test Case #%d OK!\n\n", i);
        } else {
            printf("[Wrong Answer]\n"
                    "Test Case #%u\n"
                    "Input: %u (0x%x)\n"
                    "Expect: %u\n"
                    "Output: %u\n\n",
                    i, test[i].first, test[i].first, myOut, test[i].second);
            return 0;
        }
    }
    printf("[Accepted]\n\n");
    return 0;
}