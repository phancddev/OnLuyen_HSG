#include <iostream>
#include <vector>
#define MOD 998244353
//new
using namespace std;

typedef long long ll;

ll mod_pow(ll base, ll exponent, ll mod) {
    ll result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1)
            result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);  
    cin.tie(0);                   
    cout.tie(0);                  

    int n;
    ll m;
    cin >> n >> m;

    vector<ll> pow_m(n / 2 + 1);
    pow_m[0] = 1;
    for (int i = 1; i <= n / 2; ++i) {
        pow_m[i] = pow_m[i - 1] * m % MOD;
    }

    vector<ll> dp(n + 1);
    dp[0] = 1;

    for (int i = 2; i <= n; i += 2) {
        dp[i] = 0;
        for (int l = 2; l <= i; l += 2) {
            dp[i] = (dp[i] + dp[i - l] * pow_m[l / 2] % MOD) % MOD;
        }
    }

    ll overcount = (mod_pow(m, n / 2, MOD) - m + MOD) % MOD;
    ll answer = (dp[n] - overcount + MOD) % MOD;

    cout << answer << endl;
    return 0;
}
