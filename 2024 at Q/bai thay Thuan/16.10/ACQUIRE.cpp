#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long ll;

struct Rectangle {
    ll w, h;
};

struct Line {
    ll m, c;
    double x_left;

    Line(ll _m, ll _c) : m(_m), c(_c), x_left(-1e18) {}
};

double intersection(const Line& l1, const Line& l2) {
    return (double)(l2.c - l1.c) / (l1.m - l2.m);
}

int main() {
    freopen("ACQUIRE.INP", "r", stdin);
    freopen("ACQUIRE.OUT", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    vector<Rectangle> rects(N);
    for (int i = 0; i < N; ++i) {
        cin >> rects[i].w >> rects[i].h;
    }

    sort(rects.begin(), rects.end(), [](const Rectangle& a, const Rectangle& b) {
        if (a.w != b.w)
            return a.w < b.w;
        else
            return a.h > b.h;
    });

    vector<Rectangle> filtered;
    for (const auto& rect : rects) {
        while (!filtered.empty() && filtered.back().h <= rect.h) {
            filtered.pop_back();
        }
        filtered.push_back(rect);
    }

    int M = filtered.size();
    vector<ll> dp(M + 1, 0);
    deque<Line> hull;

    hull.emplace_back(filtered[0].h, dp[0]);

    for (int i = 1; i <= M; ++i) {
        ll w = filtered[i - 1].w;

        while (hull.size() >= 2 && hull[0].m * w + hull[0].c >= hull[1].m * w + hull[1].c) {
            hull.pop_front();
        }
        dp[i] = hull.front().m * w + hull.front().c;

        if (i < M) {
            Line new_line(filtered[i].h, dp[i]);
            while (hull.size() >= 1) {
                Line& last = hull.back();
                if (last.m == new_line.m) {
                    if (last.c <= new_line.c) {
                        break;
                    } else {
                        hull.pop_back();
                        continue;
                    }
                }
                double x = intersection(last, new_line);
                if (x <= last.x_left) {
                    hull.pop_back();
                } else {
                    new_line.x_left = x;
                    break;
                }
            }
            if (hull.empty()) {
                new_line.x_left = -1e18;
            }
            hull.push_back(new_line);
        }
    }

    cout << dp[M] << endl;

    return 0;
}
