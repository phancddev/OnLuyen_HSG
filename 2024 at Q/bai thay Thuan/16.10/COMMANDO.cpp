#include <iostream>
#include <vector>
#include <deque>
#include <limits>
using namespace std;
typedef long long ll;

struct Line {
    ll m, c;
    double x_left;
    Line(ll _m = 0, ll _c = 0) : m(_m), c(_c), x_left(-numeric_limits<double>::infinity()) {}
};

double intersect(const Line& l1, const Line& l2) {
    if (l1.m == l2.m) return numeric_limits<double>::infinity();
    return (double)(l2.c - l1.c) / (l1.m - l2.m);
}

int main() {
    freopen("COMMANDO.INP", "r", stdin);
    freopen("COMMANDO.OUT", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    ll a, b, c_input;
    cin >> n >> a >> b >> c_input;

    vector<ll> x(n + 1), S(n + 1), dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        S[i] = S[i - 1] + x[i];
    }

    deque<Line> hull;
    dp[0] = 0;

    ll m_k = -2LL * a * S[0];
    ll c_k = dp[0] + a * S[0] * S[0] - b * S[0];
    hull.emplace_back(m_k, c_k);

    for (int i = 1; i <= n; ++i) {
        ll A_i = a * S[i] * S[i] + b * S[i] + c_input;

        while (hull.size() >= 2 && hull[0].m * S[i] + hull[0].c <= hull[1].m * S[i] + hull[1].c) {
            hull.pop_front();
        }
        ll max_value = hull.front().m * S[i] + hull.front().c;

        dp[i] = A_i + max_value;

        m_k = -2LL * a * S[i];
        c_k = dp[i] + a * S[i] * S[i] - b * S[i];

        Line new_line(m_k, c_k);

        while (hull.size() >= 2) {
            Line& l1 = hull[hull.size() - 2];
            Line& l2 = hull.back();
            double x1 = intersect(l1, l2);
            double x2 = intersect(l2, new_line);
            if (x2 <= x1) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(new_line);
    }

    cout << dp[n] << '\n';
    return 0;
}   
