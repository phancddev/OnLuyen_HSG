#include <iostream>
#include <vector>
using namespace std; 
#define M 1000000
int a[M + 6];
int f[10001];
int main(){
    freopen("ex.inp", "r", stdin);
    freopen("ex.out", "w", stdout);
    for(int i = 1; i <= 1000; i++) f[i] = 0;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) f[a[i]] += 1;
    for(int i = 1; i <= 1000; i++)
        if(f[i]) cout << i << ' ' << f[i] << '\n';
    
    return 0;
}