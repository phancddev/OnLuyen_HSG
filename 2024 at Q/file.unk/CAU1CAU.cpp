#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool prime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}


int divi(int num) {
    int count = 0;
    for (int i = 1; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            if (num / i == i) count++; 
            else count += 2;
        }
    }
    return count;
}

int main() {
    ifstream inputFile("CAU1.INP");
    ofstream outputFile("CAU1.OUT");

    
    

    int T;
    inputFile >> T;

    while (T--) {
        int a, b;
        inputFile >> a >> b;

        int count = 0;

        for (int num = a; num <= b; ++num) {
            int diviC = divi(num);
            if (prime(diviC)) {
                count++;
            }
        }

        outputFile << count << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}