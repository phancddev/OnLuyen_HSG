#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    
    ifstream inFile("PT.INP");
    if (!inFile.is_open()) {
        cerr << "Unable to open input file." << endl;
        return 1;
    }


    ofstream outFile("PT.OUT");
    if (!outFile.is_open()) {
        cerr << "Unable to open output file." << endl;
        return 1;
    }

    int N;
    inFile >> N;


    vector<int> scores(N);
    for (int i = 0; i < N; ++i) {
        inFile >> scores[i];
    }

   
    int Q = scores[0];
    for (int i = 1; i < N; ++i) {
        Q = gcd(Q, scores[i]);
    }

 
    outFile << Q;


    inFile.close();
    outFile.close();

    return 0;
}

