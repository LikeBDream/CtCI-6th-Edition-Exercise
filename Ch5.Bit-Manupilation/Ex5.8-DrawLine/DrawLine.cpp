// Draw Line：一个黑白屏幕被存储为单个字节数组，允许将8个连续像素存储在一个字节中。
// 屏幕的宽度为w，其中w可被8整除（也就是说，没有字节将被跨行分割）。
// 当然，屏幕的高度可以从数组的长度和宽度推算出。
// 实现一个从 (x1, y) 到 (x2, y) 画一条水平线的函数:
// drawLine(vector<uint8_t>& screen, int w, int x1, int x2, int y)

#include <iostream>
#include <vector>
#include <bitset>
#include <cstdint>

using namespace std;

void drawLine(vector<uint8_t>& screen, int w, int x1, int x2, int y) {
    unsigned int startByte = y * w / 8 + x1 / 8;
    unsigned int endByte = y * w / 8 + x2 / 8;
    for (int i = startByte; i <= endByte; i++) {
        if (i == startByte) {
            screen[i] |= ((1 << (8 - x1 % 8)) - 1);
        } else if (i == endByte) {
            screen[i] |= ( 0xFF >> (7 - x2 % 8) << (7 - x2 % 8));
        } else {
            screen[i] = 0xFF;
        }
    }
}

void GptDrawLine(vector<uint8_t>& screen, int w, int x1, int x2, int y) {
    int bytesPerRow = w / 8;
    int rowOffset = y * bytesPerRow;
    int startByte = x1 / 8;
    int startBit = x1 % 8;
    int endByte = x2 / 8;
    int endBit = x2 % 8;

    if (startByte == endByte) {
        // 起點與終點在同一個 byte
        uint8_t mask = (uint8_t)(((0xFF >> startBit) & (0xFF << (7 - endBit))));
        screen[rowOffset + startByte] |= mask;
    } else {
        screen[rowOffset + startByte] |= (0xFF >> startBit);
        screen[rowOffset + endByte] |= (0xFF << (7 - endBit));
        // 中間完整 byte
        for (int b = startByte + 1; b < endByte; ++b) {
            screen[rowOffset + b] = 0xFF;
        }
    }
}

// 輔助函數：輸出整個畫面
void printScreen(const vector<uint8_t>& screen, int w) {
    int bytesPerRow = w / 8;
    int rows = screen.size() / bytesPerRow;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < bytesPerRow; ++x) {
            cout << bitset<8>(screen[y * bytesPerRow + x]) << " ";
        }
        cout << endl;
    }
}

int main() {
    int w = 16;  // 螢幕寬度 (必須能被 8 整除)
    int h = 4;   // 螢幕高度
    vector<uint8_t> screen((w / 8) * h, 0);
    vector<uint8_t> gptScreen((w / 8) * h, 0);

    cout << "初始畫面：" << endl;
    printScreen(screen, w);

    cout << "\n畫線 (x1=3, x2=12, y=1):" << endl;
    drawLine(screen, w, 3, 12, 1);
    printScreen(screen, w);

    cout << "\n畫線 (x1=0, x2=7, y=2):" << endl;
    drawLine(screen, w, 0, 7, 2);
    printScreen(screen, w);

    cout << "\n畫線 (x1=5, x2=15, y=3):" << endl;
    drawLine(screen, w, 5, 15, 3);
    printScreen(screen, w);

    cout << "\nGPT畫線 (x1=3, x2=12, y=1):" << endl;
    GptDrawLine(gptScreen, w, 3, 12, 1);
    GptDrawLine(gptScreen, w, 0, 7, 2);
    GptDrawLine(gptScreen, w, 5, 15, 3);
    printScreen(gptScreen, w);
    cout << endl;

    return 0;
}