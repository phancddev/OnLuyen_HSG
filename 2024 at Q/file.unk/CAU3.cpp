#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    
    ifstream inputFile("CAU3.inp");
    ofstream outputFile("CAU3.out");

   
    int N, K;
    inputFile >> N >> K;

    int* a = new int[N];
    for (int i = 0; i < N; ++i) {
        inputFile >> a[i];
    }

    unordered_map<int, int> cMap;
    long long pC = 0;

    for (int i = 0; i < N; ++i) {
        int target = K - a[i];
        if (cMap.find(target) != cMap.end()) {
            pC += cMap[target];
        }
        cMap[a[i]]++;
    }

    outputFile << pC << endl;

    delete[] a;
    inputFile.close();
    outputFile.close();

    return 0;
}