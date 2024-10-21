#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

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

ll gcd_array(const vector<ll>& arr) {
    ll result = arr[0];
    for (size_t i = 1; i < arr.size(); i++) {
        result = __gcd(result, arr[i]);
    }
    return result;
}

bool is_solvable(const vector<ll>& a, ll M_prime) {
    ll g = gcd_array(a);
    return M_prime % g == 0;
}

unordered_map<ll, ll> memo;

ll dp(int idx, ll M_prime, const vector<ll>& a) {
    if (M_prime == 0) {
        return 1;
    }
    if (M_prime < 0 || idx >= (int)a.size()) {
        return 0;
    }

    ll key = M_prime * 1000000LL + idx;
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    ll ways = dp(idx + 1, M_prime, a) % MOD;
    ways = (ways + dp(idx, M_prime - a[idx], a)) % MOD;

    memo[key] = ways;
    return ways;
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

    ll sum_a = accumulate(a.begin(), a.end(), 0LL);
    if (M < sum_a) {
        cout << 0 << '\n';
        return 0;
    }

    ll M_prime = M - sum_a;
    if (!is_solvable(a, M_prime)) {
        cout << 0 << '\n';
        return 0;
    }

    if (all_one) {
        ll n = N;
        ll r = M - N;
        ll res = 1;
        for (ll i = 1; i <= n - 1; i++) {
            res = res * (r + i) % MOD;
            res = res * powmod_func(i, MOD - 2, MOD) % MOD;
        }
        cout << res << '\n';
        return 0;
    }

    if (N <= 20) {
        memo.clear();
        ll ways = dp(0, M_prime, a);
        cout << ways << '\n';
        return 0;
    }

    cout << 0 << '\n';
    return 0;
}
