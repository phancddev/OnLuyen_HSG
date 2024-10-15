#include <bits/stdc++.h>
using namespace std;

const int N = 1001;
int a[N][N], b[N][N];
vector<int> c;
int n, m, t;
long long x = 0;

struct D {
    vector<int> p, l, cur;
    D(int n): p(n + 5), l(n + 5), cur(n + 5) {
        for (int i = 0; i <= n; ++i) {
            p[i] = i;
            l[i] = 1;
        }
        for (int i : c) {
            cur[i]++;
        }
    }
    int rt(int i) {
        if (i != p[i]) return p[i] = rt(p[i]);
        return i;
    }
    bool jj(int u, int v, int d) {
        u = rt(u);
        v = rt(v);
        if (u == v) return false;
        if (l[v] < l[u]) swap(u, v);
        l[u] += l[v];
        p[v] = u;
        cur[u] += cur[v];
        if (l[u] >= t) {
            x += 1LL * cur[u] * d;
            cur[u] = 0;
        }
        return true;
    }
};

struct E {
    int u, v, d;
    E(int x, int y, int z): u(x), v(y), d(z) {}
    bool operator<(const E& t) const {
        return d < t.d;
    }
};

vector<E> f;

void iHM() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (i) {
                f.push_back(E(i * m + j, (i - 1) * m + j, abs(a[i][j] - a[i - 1][j])));
            }
            if (j) {
                f.push_back(E(i * m + j, i * m + j - 1, abs(a[i][j] - a[i][j - 1])));
            }
        }
    }
}

void iSP() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> b[i][j];
            if (b[i][j]) {
                c.push_back(i * m + j);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("HILL.INP", "r", stdin);
    freopen("HILL.OUT", "w", stdout);
    cin >> n >> m >> t;
    iHM();
    iSP();
    if (t == 1) {
        cout << 0 << '\n';
        return 0;
    }
    sort(f.begin(), f.end());
    D d(n * m);
    for (E &t : f) {
        d.jj(t.u, t.v, t.d);
    }
    cout << x;
    return 0;
}
