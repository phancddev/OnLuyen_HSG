#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 5001;
const int MOD = 998244353;

ll pow2_arr[5001];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    pow2_arr[0] = 1;
    for(int k = 1; k <= 5000; ++k){
        pow2_arr[k] = (pow2_arr[k - 1] * 2) % MOD;
    }
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> grid(n + 1, vector<int>(n + 1, 0));
        for(int i = 0; i < n; ++i){
            int l, r;
            cin >> l >> r;
            grid[l][r]++;
        }

        vector<ll> sumA_prev(n + 2, 0);
        vector<ll> sumA_current(n + 2, 0);
        vector<ll> sumC_prev(n + 1, 0);
        vector<ll> sumC_current(n + 1, 0);
        ll total = 0;
        
        for(int a = 1; a <= n; ++a){
            for(int b = n; b >= 1; --b){
                sumA_current[b] = grid[a][b];
                if(a > 1){
                    sumA_current[b] += sumA_prev[b];
                    if(sumA_current[b] >= MOD) sumA_current[b] -= MOD;
                }
                if(b < n){
                    sumA_current[b] += sumA_current[b + 1];
                    if(sumA_current[b] >= MOD) sumA_current[b] -= MOD;
                }
                if(a > 1 && b < n){
                    sumA_current[b] -= sumA_prev[b + 1];
                    if(sumA_current[b] < 0) sumA_current[b] += MOD;
                }
            }
            
            for(int b = 1; b <= n; ++b){
                sumC_current[b] = sumC_prev[b] + grid[a][b];
                if(sumC_current[b] >= MOD) sumC_current[b] -= MOD;
            }
            
            for(int b = 1; b <= n; ++b){
                if(a > b){
                    ll A = sumA_current[b];
                    ll B = sumA_current[b] - sumA_prev[b];
                    if(B < 0) B += MOD;
                    ll C = sumC_current[b];
                    ll D = grid[a][b];
                    ll AB_C_D = (A - B - C + D) % MOD;
                    if(AB_C_D < 0) AB_C_D += MOD;

                    ll x1 = (A >= 0 && A <= 5000) ? pow2_arr[A] : 0;
                    ll x2 = ((A - B) >= 0 && (A - B) <= 5000) ? pow2_arr[A - B] : 0;
                    ll x3 = ((A - C) >= 0 && (A - C) <= 5000) ? pow2_arr[A - C] : 0;
                    ll x4 = ((AB_C_D) >= 0 && (AB_C_D) <= 5000) ? pow2_arr[AB_C_D] : 0;
                    ll count = (x1 - x2 - x3 + x4) % MOD;
                    if(count < 0) count += MOD;
                    total = (total + ((a - b) * count) % MOD) % MOD;
                }
            }
            
            for(int b = 1; b <= n; ++b){
                sumA_prev[b] = sumA_current[b];
                sumC_prev[b] = sumC_current[b];
            }
            
            fill(sumA_current.begin(), sumA_current.end(), 0LL);
            fill(sumC_current.begin(), sumC_current.end(), 0LL);
        }
        cout << total % MOD << "\n";
    }
}
