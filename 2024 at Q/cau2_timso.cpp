#include <iostream>
#include <fstream>
#define ll long long

using namespace std;

// Euclid (__gcd)
ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll countM(ll a, ll b, ll x) {
    return (x / a) + (x / b) - (x / lcm(a, b));
}

ll findNum(ll a, ll b, ll N) {
    ll low = 1, high = 2e18, result = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (countM(a, b, mid) >= N) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    ifstream inputFile("CAU2.INP");
    ofstream outputFile("CAU2.OUT");



    int T;
    inputFile >> T;

    while (T--) {
        ll a, b, N;
        inputFile >> a >> b >> N;

        ll result = findNum(a, b, N);
        outputFile << result << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}