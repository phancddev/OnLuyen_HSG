#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;
const int MAX = 1000005;

ll powmod_func(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1LL) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1LL;
    }
    return res;
}

ll factorial_arr[MAX];
ll inv_factorial_arr[MAX];

void precompute_factorials(int max_n) {
    factorial_arr[0] = 1;
    for (int i = 1; i <= max_n; i++) {
        factorial_arr[i] = factorial_arr[i - 1] * i % MOD;
    }
    inv_factorial_arr[max_n] = powmod_func(factorial_arr[max_n], MOD - 2, MOD);
    for (int i = max_n - 1; i >= 0; i--) {
        inv_factorial_arr[i] = inv_factorial_arr[i + 1] * (i + 1) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    ll M;
    cin >> N >> M;
    vector<ll> a(N);
    bool all_one = true;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (a[i] != 1) {
            all_one = false;
        }
    }
    if (all_one && N - 1 < MAX) {
        precompute_factorials(N - 1);
    }
    if (all_one) {
        if (M < N) {
            cout << 0;
            return 0;
        }
        if (N - 1 >= MAX) {
        } else {
            if (factorial_arr[0] == 0) {
                precompute_factorials(N - 1);
            }
        }
        ll numerator = 1;
        for (int k = 0; k < N - 1; k++) {
            ll term = (M - 1 - k) % MOD;
            if (term < 0) {
                term += MOD;
            }
            numerator = numerator * term % MOD;
        }
        ll denominator = factorial_arr[N - 1];
        ll inv_denominator = inv_factorial_arr[N - 1];
        ll Q = numerator * inv_denominator % MOD;
        cout << Q;
        return 0;
    } else {
        if (N <= 1000 && M <= 5000) {
            ll sum_a = 0;
            for (auto &x : a) sum_a += x;
            if (M < sum_a) {
                cout << 0;
                return 0;
            }
            ll M_prime = M - sum_a;
            vector<int> dp(M_prime + 1, 0);
            dp[0] = 1;
            for (int i = 0; i < N; i++) {
                ll ai = a[i];
                for (ll m = ai; m <= M_prime; m++) {
                    dp[m] = (dp[m] + dp[m - ai]) % MOD;
                }
            }
            cout << dp[M_prime];
            return 0;
        } else {
            cout << 0;
            return 0;
        }
    }
}
