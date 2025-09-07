// Flip Bit to Win: You have an integer and you can flip exactly one bit from a O to a 1. Write code to
// find the length of the longest sequence of 1 s you could create.
// EXAMPLE
// Input:  1775 (or: 11011101111)
// Output: 8

#include <stdio.h>

unsigned int FlipBitToWin(unsigned int num) {
    if (num == 0U)
        return 1U;
    if (num == ~0U)
        return 32U;
    unsigned int maxLen = 0, curLen = 0, preLen = 0;
    bool preIsZero = 0;
    // parsing bits
    while (num) {
        if (num % 2) {
            curLen++;
            preIsZero = 0;
        } else {
            if (preIsZero) {
                preLen = 0;
            } else {
                int temp = preLen + 1 + curLen;
                maxLen = (maxLen < temp) ? temp : maxLen;
                preLen = curLen;
                curLen = 0;
                preIsZero = 1;
            }
        }
        num >>= 1;
    }
    if (curLen) {
        int temp = preLen + 1 + curLen;
        maxLen = (maxLen < temp) ? temp : maxLen;
    }
    return maxLen;
}
int main() {
    const unsigned int input[] = {
        1775,  // b'11011101111
        0,
        511,   // b'111111111
        1022,  // b'1111111110
        2559,  // b'1011111111 = 2048+511
        0b110111001111U,
        0b1100111001111U,
        ~0U,
        ((~0U>>2)<<2 | 1U),
    };
    const unsigned int output[] = {
        8,
        1,
        10,
        10,
        10,
        6,
        5,
        32,
        32,
    };
    for (int i = 0; i < sizeof(input) / sizeof(int); i++) {
        int myOut = FlipBitToWin(input[i]);
        if (myOut == output[i]) {
            printf("Test Case #%d OK!\n\n", i);
        } else {
            printf("[Wrong Answer]\n"
                    "Test Case #%u\n"
                    "Input: %u (0x%x)\n"
                    "MyOut: %u\n"
                    "Expect: %u\n\n",
                    i, input[i], input[i], myOut, output[i]);
            return 0;
        }
    }
    printf("[Accepted]\n\n");
    return 0;
}