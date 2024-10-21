#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0)
                s += '0';
            else
                s += '1';
        }
        cout << s << endl;
    }
    return 0;
}
