#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inFile("MK.INP");
    std::ofstream outFile("MK.OUT");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Unable to open input or output file." << std::endl;
        return 1;
    }

 
    std::string N;
    inFile >> N;


    int M = 0;
    for (char digit : N) {
        M += digit - '0';
    }

   
    outFile << M << std::endl;

    
    inFile.close();
    outFile.close();

    return 0;
}

