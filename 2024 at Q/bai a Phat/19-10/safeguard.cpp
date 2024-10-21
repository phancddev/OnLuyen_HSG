#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;
struct Point {
    ll x, y;
    bool operator<(const Point &p) const {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }
    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
};

ll cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point> &points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int n = points.size();
    vector<Point> hull;

    if (n == 1) {
        hull.push_back(points[0]);
        return hull;
    }

    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) < 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    int t = hull.size() + 1;
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() >= t && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) < 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    if (hull.size() > 1 && hull.front() == hull.back())
        hull.pop_back();

    return hull;
}

ll polygonArea(const vector<Point> &poly) {
    ll area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i) {
        area += (poly[i].x * poly[(i + 1) % n].y) - (poly[(i + 1) % n].x * poly[i].y);
    }
    return abs(area);
}

bool pointInCP(const vector<Point> &hull, const Point &p) {
    int n = hull.size();
    if (n < 3)
        return false;

    if (cross(hull[0], hull[1], p) < 0 || cross(hull[0], hull[n - 1], p) > 0)
        return false;

    int left = 1, right = n - 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (cross(hull[0], hull[mid], p) >= 0)
            left = mid;
        else
            right = mid;
    }
    
    ll s = abs(cross(hull[0], hull[left], hull[right]));
    ll s1 = abs(cross(hull[0], hull[left], p));
    ll s2 = abs(cross(hull[left], hull[right], p));
    ll s3 = abs(cross(hull[right], hull[0], p));

    return s1 + s2 + s3 <= s;
}

int main() {
    //NEW3
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n;
    vector<Point> dogs(n);
    for (int i = 0; i < n; ++i)
        cin >> dogs[i].x >> dogs[i].y;

    vector<Point> hull = convexHull(dogs);
    ll area = polygonArea(hull);

    cin >> k;
    vector<Point> chickens(k);
    for (int i = 0; i < k; ++i)
        cin >> chickens[i].x >> chickens[i].y;

    int safeChickens = 0;
    if (area > 0) {
        for (int i = 0; i < k; ++i) {
            if (pointInCP(hull, chickens[i]))
                ++safeChickens;
        }
    }

    cout << safeChickens << '\n';
    return 0;
}
