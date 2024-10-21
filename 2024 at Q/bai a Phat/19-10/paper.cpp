#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    ll cross(const Point& p) const { return x * p.y - y * p.x; }
    ll dot(const Point& p) const { return x * p.x + y * p.y; }
    ll length2() const { return x * x + y * y; }
    bool operator < (const Point& p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator == (const Point& p) const { return x == p.x && y == p.y; }
};

vector<Point> convexHull(vector<Point>& P) {
    int n = P.size(), k = 0;
    vector<Point> H(2 * n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; i++) {
        while (k >= 2 && (H[k - 1] - H[k - 2]).cross(P[i] - H[k - 2]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && (H[k - 1] - H[k - 2]).cross(P[i] - H[k - 2]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k);
    if (n > 1) H.pop_back();
    return H;
}

double minimalWidth(vector<Point>& P) {
    int n = P.size();
    if (n <= 2) return 0.0;
    bool colinear = true;
    Point base = P[1] - P[0];
    for (int i = 2; i < n; i++) {
        if (abs(base.cross(P[i] - P[0])) != 0) {
            colinear = false;
            break;
        }
    }
    if (colinear) return 0.0;

    double minWidth = 1e20;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        Point edge = P[ni] - P[i];
        double edgeLen = sqrt(edge.length2());
        Point edgeDir(edge.x / edgeLen, edge.y / edgeLen);

        while (true) {
            int nj = (j + 1) % n;
            ll area1 = abs(edge.cross(P[j] - P[i]));
            ll area2 = abs(edge.cross(P[nj] - P[i]));
            if (area2 > area1) {
                j = nj;
            } else {
                break;
            }
        }
        ll numerator = abs(edge.cross(P[j] - P[i]));
        double width = numerator / edgeLen;
        if (width < minWidth) minWidth = width;
    }
    return minWidth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> P(n);
    for (int i = 0; i < n; i++) {
        cin >> P[i].x;
    }
    for (int i = 0; i < n; i++) {
        cin >> P[i].y;
    }
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());
    if (P.size() <= 1) {
        cout << "0.0000000000\n";
        return 0;
    }
    vector<Point> hull = convexHull(P);
    double minWidth = minimalWidth(hull);
    cout << fixed << setprecision(10) << minWidth << '\n';
    return 0;
}
