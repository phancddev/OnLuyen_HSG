#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream inFile("TS.INP");
    std::ofstream outFile("TS.OUT");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Unable to open input or output file." << std::endl;
        return 1;
    }

  
    std::freopen("TS.INP", "r", stdin);
    std::freopen("TS.OUT", "w", stdout);

    int N;
    std::cin >> N;

    std::unordered_map<int, int> countMap;

    for (int i = 0; i < N; ++i) {
        int num;
        std::cin >> num;
        countMap[num]++;
    }

    for (const auto& entry : countMap) {
        if (entry.second > 1) {
            std::cout << entry.first << " " << entry.second << std::endl;
        }
    }

    return 0;
}

