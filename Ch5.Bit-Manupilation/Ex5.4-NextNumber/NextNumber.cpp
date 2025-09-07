// Next Number：给定一个正整数，打印下一个較小的数字和下一个較大的数字，
// 满足它们的二进制表示中1的位数相同。
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

// 回傳 {nextSmaller, nextLarger}. 如果不存在，回傳 {-1, -1}
pair<int,int> nextNumber(int n) {
    int smaller = -1, larger = -1;

    return {smaller, larger};
}

pair<int,int> GptNextNumber(int n) {
    int c = n;
    int c0_l = 0, c1_l = 0; // nextLarger: 右側連續 0 和 1
    int c0_s = 0, c1_s = 0; // nextSmaller: 右側連續 0 和 1

    // 計算 nextLarger 所需 c0_l, c1_l
    while (((c & 1) == 0) && (c != 0)) { c0_l++; c >>= 1; }
    while ((c & 1) == 1) { c1_l++; c >>= 1; }
    // nextLarger
    int nextL = -1;
    if (!(c0_l + c1_l == 31 || c0_l + c1_l == 0)) {
        int p = c0_l + c1_l;
        nextL = n | (1 << p);
        nextL &= ~((1 << p) - 1);
        nextL |= (1 << (c1_l - 1)) - 1;
    }

    // 計算 nextSmaller 所需 c1_s, c0_s
    c = n;
    while ((c & 1) == 1) { c1_s++; c >>= 1; }
    while (((c & 1) == 0) && (c != 0)) { c0_s++; c >>= 1; }
    // nextSmaller
    int nextS = -1;
    if (c0_s + c1_s != 0) {
        int p = c0_s + c1_s;
        nextS = n & (~0 << (p + 1));
        int mask = (1 << (c1_s + 1)) - 1;
        nextS |= mask << (c0_s - 1);
    }

    return {nextS, nextL};
}

void runTest(int n) {
    auto [smaller, larger] = nextNumber(n);
    auto [smallerG, largerG] = GptNextNumber(n);

    cout << "數字: " << n << endl;
    cout << "二進位: " << bitset<16>(n) << endl;
    cout << "相同1數量的下一個較小數: " << smaller 
         << " (" << bitset<16>(smaller) << ")" << endl;
    cout << "GPT算出的下一個較小數:   " << smallerG 
         << " (" << bitset<16>(smallerG) << ")" << endl;
    cout << "相同1數量的下一個較大數: " << larger 
         << " (" << bitset<16>(larger) << ")" << endl;
    cout << "GPT算出的下一個較大數:   " << largerG
         << " (" << bitset<16>(largerG) << ")" << endl;
    cout << "--------------------------------" << endl;
}

int main() {
    vector<int> tests = {
        0b10110,   // 22
        0b10011110000011, // 10115
        0b1,       // 邊界 case
        0b111,     // 7，沒有更大的
        0b100111000, // 312
        13948      // CTCI 書中範例
    };

    for (int n : tests) {
        runTest(n);
    }

    return 0;
}
