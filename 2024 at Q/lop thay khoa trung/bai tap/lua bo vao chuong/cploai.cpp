#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("cploai.inp", "r", stdin);
    freopen("cploai.out", "w", stdout);
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i <= n; i++) {
        cin >> a[i];

    }
    
    // for (int i = 0; i < n - 1; i++) {
    //     for (int j = i+1; j < n; j++) {
    //         if (a[i] > a[j]) {
    //             swap(a[i], a[j]);
    //             // int temp = a[i];
    //             // a[i] = a[j];
    //             // a[j] = temp;
    //         }
    //     }
    // }
    sort(a, a+n);
        int countWood = 1;
        for( int i = 1; i < n; i++) {
            if (a[i] != a[i-1])  {
                countWood++;
            }
        }
        
        cout << countWood << "\n";
        cout << a[0] << " ";
        
        for (int i = 1; i < n;i++) {
            if (a[i] != a[i-1])  {
                cout << a[i] << " " ;
            }
        }
return 0;
}
