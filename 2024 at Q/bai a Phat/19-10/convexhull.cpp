#include <iostream>
#include <algorithm>
#include <vector>
typedef long long ll;
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point &p) const {
        if (x != p.x)
            return x < p.x;
        else
            return y < p.y;
    }
};

const int MAXN = 200005;
Point points[MAXN];

ll cross(const Point &O, const Point &A, const Point &B) {
    return (ll)(A.x - O.x) * (B.y - O.y) - (ll)(A.y - O.y) * (B.x - O.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> points[i].x >> points[i].y;

    sort(points, points + n);

    vector<Point> hull;

    for(int i = 0; i < n; ++i) {
        while(hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) < 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    int t = hull.size() + 1;
    for(int i = n-2; i >= 0; --i) {
        while(hull.size() >= t && cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) < 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    if(hull.size() > 1 && hull.front().x == hull.back().x && hull.front().y == hull.back().y)
        hull.pop_back();

    cout << (int)hull.size() << '\n';
    for(size_t i = 0; i < hull.size(); ++i)
        cout << hull[i].x << ' ' << hull[i].y << '\n';

    return 0;
}
