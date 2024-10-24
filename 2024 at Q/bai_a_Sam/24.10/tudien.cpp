#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
typedef long long ll;

struct Factorial {
    vector<ll> fact;
    int mod;

    Factorial(int n, int mod) : mod(mod) {
        fact.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i % mod;
    }

    ll get(int n) {
        return fact[n];
    }
};

struct BIT {
    vector<int> tree;
    int n;

    BIT(int n) : n(n) {
        tree.resize(n + 2, 0);
    }

    void update(int idx) {
        while (idx <= n) {
            tree[idx] += 1;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int res = 0;
        while (idx) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    int queryRange(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct PermutationRank {
    int N;
    vector<int> T;
    vector<int> sorted_T;
    unordered_map<int, int> val_to_idx;

    PermutationRank(int N, vector<int>& T) : N(N), T(T) {
        sorted_T = T;
        sort(sorted_T.begin(), sorted_T.end());
        for (int i = 0; i < N; ++i) {
            val_to_idx[sorted_T[i]] = i + 1;
        }
    }

    int computeRank() {
        Factorial factorial(N, MOD);
        BIT bit(N);
        ll rank = 0;

        for (int i = 0; i < N; ++i) {
            int idx = val_to_idx[T[i]];
            int c_i = idx - 1 - bit.query(idx - 1);
            rank = (rank + c_i * factorial.get(N - i - 1)) % MOD;
            bit.update(idx);
        }

        return (rank + 1) % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }

    PermutationRank permRank(N, T);
    cout << permRank.computeRank() << endl;

    return 0;
}
