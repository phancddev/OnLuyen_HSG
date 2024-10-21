#include <iostream>
#include <vector>
#include <deque>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
    ll m, c; 
    Line(ll _m = 0, ll _c = 0) : m(_m), c(_c) {}
};


double intersect(const Line& l1, const Line& l2) {
    return (double)(l2.c - l1.c) / (l1.m - l2.m);
}
//new 2
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("319C.INP", "r", stdin);
    freopen("319C.OUT", "w", stdout);

    int n;
    cin >> n;
    vector<ll> h(n), c(n), dp(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> c[i];

    deque<Line> hull;
    dp[0] = 0;
    hull.emplace_back(c[0], dp[0]);

    for (int i = 1; i < n; ++i) {
        
        while (hull.size() >= 2 && hull[0].m * h[i] + hull[0].c >= hull[1].m * h[i] + hull[1].c) {
            hull.pop_front();
        }
        dp[i] = hull.front().m * h[i] + hull.front().c;

        Line new_line(c[i], dp[i]);
        
        while (hull.size() >= 2) {
            Line l1 = hull[hull.size() - 2];
            Line l2 = hull.back();
            if (intersect(l1, l2) >= intersect(l2, new_line)) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(new_line);
    }

    cout << dp[n - 1] << endl;
    return 0;
}
