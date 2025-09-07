// Ex5.6 Conversion：编写一个函数，以确定需要翻转多少位才能将整数A转换为整数B。
// Input: 29 (or: 11101), 15 (or: 01111)
// Output: 2

#include <stdio.h>
#include <vector>

unsigned int BitConversion(unsigned int a, unsigned int b) {
    unsigned int xorNum = a ^ b;
    unsigned int ans = 0;
    while (xorNum) {
        if (xorNum & 1)
            ans++;
        xorNum >>= 1;
    }
    return ans;
}

int main() {
    std::vector<std::vector<unsigned int>> test = {
        {0b11101U, 0b01111U, 2U},
        {0U, 1U, 1U},
        {0U, 0U, 0U},
        {~0U, ~0U, 0U},
        {0b11110110101U, 0b011010110111111U, 5U},
        // 011010110111111U
        //     11110110101U
    };
    for (int i = 0; i < test.size(); i++) {
        int myOut = BitConversion(test[i][0], test[i][1]);
        if (myOut == test[i][2]) {
            printf("Test Case #%d OK!\n\n", i);
        } else {
            printf("[Wrong Answer]\n"
                    "Test Case #%u\n"
                    "Input: 0x%x ,0x%x)\n"
                    "Expect: %u\n"
                    "Output: %u\n\n",
                    i, test[i][0], test[i][1], test[i][2], myOut);
            return 0;
        }
    }
    printf("[Accepted]\n\n");
    return 0;
}