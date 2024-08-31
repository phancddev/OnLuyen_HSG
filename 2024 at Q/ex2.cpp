#include <bits/stdc++.h>
#define M 1000000
using namespace std;
//const int M=1000000;

int a[M+6];
int f[1001];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("vd1.inp", "r",stdin);
    freopen("vd1.out","w",stdout);
    for (int i=1; i<=1000; i++) f[i]=0;
    int n;
    cin>>n;
    for (int i=1; i<=n; i++) cin>>a[i];
    for (int i=1; i<=n; i++) f[a[i]]+=1;
    for (int i=1; i<=1000; i++)
        if (f[i]>0) cout<<i<< ' '<<f[i]<<'\n';
    return 0;
}