#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    freopen("GCD.INP", "r", stdin);
    freopen("GCD.OUT", "w", stdout);

    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int G;
        cin >> G;

        int count = 0;
        for (int l = 0; l < N; l++) {
            int currentGCD = 0;
            for (int r = l; r < N; r++) {
                currentGCD = gcd(currentGCD, arr[r]);
                if (currentGCD == G) {
                    count++;
                }
                if (currentGCD < G) break;
            }
        }

        cout << count << endl;
    }

    return 0;
}
