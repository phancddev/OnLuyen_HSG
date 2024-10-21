#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;

int main(){
    freopen("cakes.inp", "r", stdin);
    freopen("cakes.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N, T, K;
    cin >> N >> T >> K;
    
    vector<vector<ll>> C(T+1, vector<ll>(T+1, 0));
    for(int i=1;i<=T;i++){
        for(int j=1;j<=T;j++){
            cin >> C[i][j];
        }
    }
    
    vector<int> b(N+1, 0);
    for(int i=1;i<=N;i++) cin >> b[i];
    
    vector<vector<ll>> cT(T+1, vector<ll>(N+1, 0));
    for(int t=1;t<=T;t++){
        for(int i=1;i<=N;i++){
            cT[t][i] = cT[t][i-1] + C[b[i]][t];
        }
    }
    
    vector<ll> dp(N+1, INF);
    dp[0] = 0;
    
    vector<ll> cRM(T+1, INF);
    for(int t=1;t<=T;t++) cRM[t] = dp[0] - cT[t][0];
    
    for(int i=1;i<=N;i++){
        if(i >= K){
            for(int t=1;t<=T;t++){
                ll temp = dp[i-K] - cT[t][i-K];
                if(temp < cRM[t]){
                    cRM[t] = temp;
                }
            }
        }
        if(i < K){
            dp[i] = INF;
        }
        else{
            ll mV = INF;
            for(int t=1;t<=T;t++){
                ll tV = cT[t][i] + cRM[t];
                if(tV < mV){
                    mV = tV;
                }
            }
            dp[i] = mV;
        }
    }
    cout << dp[N];
}
