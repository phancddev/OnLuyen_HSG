#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

using ll = long long;
const ll INF = 1e18 + 7;
const int N = 1e5 + 1;
const int MOD = 1e9 + 7;

struct IOManager {
    int n, k, t;
    vector<int> a;
    vector<vector<ll>> c;

    void read_input() {
        cin >> n >> t >> k;
        c.resize(t + 1, vector<ll>(t + 1, INF));
        a.resize(n + 1);

        for (int i = 1; i <= t; i++) {
            for (int j = 1; j <= t; j++) {
                cin >> c[i][j];
            }
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
    }

    void write_output(ll result) {
        cout << result << "\n";
    }
};

struct Solver {
    int n, k, t;
    vector<int> a;
    vector<vector<ll>> c;
    vector<vector<ll>> dp, pre;

    Solver(int n, int k, int t, const vector<int>& a, const vector<vector<ll>>& c)
        : n(n), k(k), t(t), a(a), c(c) {
        dp.resize(n + 1, vector<ll>(t + 1, INF));
        pre.resize(n + 1, vector<ll>(t + 1, 0));
    }

    ll getsum(int l, int r, int p) {
        return pre[r][p] - pre[l - 1][p];
    }

    ll solve() {
        // Floyd-Warshall
        for (int p = 1; p <= t; p++) {
            for (int i = 1; i <= t; i++) {
                for (int j = 1; j <= t; j++) {
                    c[i][j] = min(c[i][j], c[i][p] + c[p][j]);
                }
            }
        }

      
        for (int p = 1; p <= t; p++) {
            for (int i = 1; i <= n; i++) {
                pre[i][p] = pre[i - 1][p] + c[a[i]][p];
            }
        }

        
        for (int p = 1; p <= t; p++) dp[k][p] = getsum(1, k, p);

        //dp 
        for (int i = k + 1; i <= n; i++) {
            ll tmp = INF;
            if (i - k >= k) {
                for (int p = 1; p <= t; p++) {
                    tmp = min(tmp, dp[i - k][p]);
                }
            }
            for (int p = 1; p <= t; p++) {
                dp[i][p] = min(dp[i][p], dp[i - 1][p] + c[a[i]][p]);
                dp[i][p] = min(dp[i][p], tmp + getsum(i - k + 1, i, p));
            }
        }

        //dp[n][p]
        ll res = INF;
        for (int p = 1; p <= t; p++) {
            res = min(res, dp[n][p]);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("cakes.inp", "r", stdin);
    freopen("cakes.out", "w", stdout);

    IOManager io;
    io.read_input();

    Solver solver(io.n, io.k, io.t, io.a, io.c);
    ll result = solver.solve();

    io.write_output(result);

    return 0;
}
