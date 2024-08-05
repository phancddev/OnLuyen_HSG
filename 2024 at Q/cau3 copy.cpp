#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    
    ifstream inputFile("bai3.inp");
    ofstream outputFile("bai3.out");

    if (!inputFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int N, K;
    inputFile >> N >> K;

    int* a = new int[N];
    for (int i = 0; i < N; ++i) {
        inputFile >> a[i];
    }

    unordered_map<int, int> countMap;
    long long pairCount = 0;

    for (int i = 0; i < N; ++i) {
        int target = K - a[i];
        if (countMap.find(target) != countMap.end()) {
            pairCount += countMap[target];
        }
        countMap[a[i]]++;
    }

    outputFile << pairCount << endl;

    delete[] a;
    inputFile.close();
    outputFile.close();

    return 0;
}