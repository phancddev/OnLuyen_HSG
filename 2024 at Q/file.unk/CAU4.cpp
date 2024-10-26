#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    ifstream input("CAU4.INP");
    ofstream output("CAU4.OUT");

    if (!input || !output) {
        cerr << "Không thể mở tệp tin." << endl;
        return 1;
    }

    int x, a, y, b, m;
    input >> x >> a >> y >> b >> m;

    // Hash table để lưu trữ số lần xuất hiện của mỗi độ dài
    unordered_map<int, int> woodCount;
    woodCount[a] = x;
    woodCount[b] = y;

    // Mảng để lưu tất cả các độ dài của hàng cầu
    int woodLengths[301] = {0};
    for (int i = 1; i <= x; ++i) {
        woodLengths[a * i] += i;
    }
    for (int j = 1; j <= y; ++j) {
        woodLengths[b * j] += j;
    }

    int maxWidth = 0;
    for (int width = 1; width <= 300; ++width) {
        if (woodLengths[width] >= m) {
            maxWidth = width;
        }
    }

    output << maxWidth << endl;

    input.close();
    output.close();

    return 0;
}