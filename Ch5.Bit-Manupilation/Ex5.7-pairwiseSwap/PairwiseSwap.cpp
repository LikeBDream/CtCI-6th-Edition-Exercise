// Pairwise Swap：编写一个程序，用尽可能少的指令交换整数中的奇数位和偶数位
//（例如，交换第0位和第1位，交换第2位和第3位，依此类推）。
// 目標：交換 (0,1), (2,3), (4,5) ... (30,31)

// 提示：可以用 mask 0xAAAAAAAA 與 0x55555555

#include <iostream>
#include <bitset>
using namespace std;

unsigned int pairwiseSwap(unsigned int n) {
    return ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1);
}

int main() {
    unsigned int n = 42; // 測資: 42 = 0b00101010

    cout << "原始數字: " << n << endl;
    cout << "原始二進位: " << bitset<32>(n) << endl;

    unsigned int swapped = pairwiseSwap(n);

    cout << "交換後數字: " << swapped << endl;
    cout << "交換後二進位: " << bitset<32>(swapped) << endl;

    return 0;
}
