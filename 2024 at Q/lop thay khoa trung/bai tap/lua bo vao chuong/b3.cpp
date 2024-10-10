// #include <iostream>     // For input and output
// #include <vector>       // For using vector container
// #include <algorithm>    // For sort and lower_bound functions
// #include <functional>   // For using lambda functions
// #include <fstream>      // For file I/O

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("MOON.INP", "r", stdin);
    freopen("MOON.OUT", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for(auto &x: a) cin >> x;


    sort(a.begin(), a.end(), [&](const long long &x, const long long &y) -> bool {
        return x > y;
    });

    for(int op=0; op<m; op++){
        int h_j;
        long long k_j;
        cin >> h_j >> k_j;

        for(int i=0; i<h_j; i++) a[i] -= k_j;


        if(h_j < n){

            long long threshold = a[h_j-1];


            int pos = lower_bound(a.begin() + h_j, a.end(), threshold, [&](const long long &x, const long long &y) -> bool {
                return x > y;
            }) - a.begin();


            sort(a.begin(), a.end(), [&](const long long &x, const long long &y) -> bool {
                return x > y;
            });
        }
        else{

            sort(a.begin(), a.end(), [&](const long long &x, const long long &y) -> bool {
                return x > y;
            });
        }
    }


    sort(a.begin(), a.end(), [&](const long long &x, const long long &y) -> bool {
        return x > y;
    });


    for(int i=0; i<n; i++){
        cout << a[i] << (i < n-1 ? ' ' : '\n');
    }
    return 0;
}
