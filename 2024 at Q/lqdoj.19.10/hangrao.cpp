#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-12;

struct P {
    ld x, y;
    P() {}
    P(ld _x, ld _y) : x(_x), y(_y) {}
    P operator - (const P &p) const {
        return P(x - p.x, y - p.y);
    }
    P operator + (const P &p) const {
        return P(x + p.x, y + p.y);
    }
    P operator * (ld k) const {
        return P(x * k, y * k);
    }
    P operator / (ld k) const {
        return P(x / k, y / k);
    }
    ld cross(const P &p) const {
        return x * p.y - y * p.x;
    }
    ld dot(const P &p) const {
        return x * p.x + y * p.y;
    }
    ld len() const {
        return sqrt(x * x + y * y);
    }
    ld distTo(const P &p) const {
        return (*this - p).len();
    }
};

bool cmp(const P &a, const P &b) {
    return a.x < b.x || (abs(a.x - b.x) < EPS && a.y < b.y);
}

bool ccw(const P &a, const P &b, const P &c) {
    return (b - a).cross(c - a) > EPS;
}

vector<P> hull(vector<P> pts) {
    sort(pts.begin(), pts.end(), cmp);
    pts.erase(unique(pts.begin(), pts.end(), [](const P &a, const P &b) {
        return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
    }), pts.end());
    int n = pts.size();
    if (n == 1) return pts;
    
    vector<P> h;
    for (int i = 0; i < n; ++i) {
        while (h.size() >= 2 && !ccw(h[h.size() - 2], h.back(), pts[i]))
            h.pop_back();
        h.push_back(pts[i]);
    }
    
    int sz = h.size();
    for (int i = n - 2; i >= 0; --i) {
        while (h.size() > sz && !ccw(h[h.size() - 2], h.back(), pts[i]))
            h.pop_back();
        h.push_back(pts[i]);
    }

    h.pop_back();
    return h;
}

ld rCp(const vector<P> &h, const vector<P> &pts) {
    int n = h.size();
    if (n <= 1) return 0.0;
    
    ld minA = numeric_limits<ld>::max();

    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        P edge = h[ni] - h[i];
        P eDir = edge / edge.len();
        P eNorm(-eDir.y, eDir.x);

        ld minProjE = numeric_limits<ld>::max(), maxProjE = -numeric_limits<ld>::max();
        ld minProjN = numeric_limits<ld>::max(), maxProjN = -numeric_limits<ld>::max();

        for (const auto &p : pts) {
            ld projE = eDir.dot(p), projN = eNorm.dot(p);
            minProjE = min(minProjE, projE);
            maxProjE = max(maxProjE, projE);
            minProjN = min(minProjN, projN);
            maxProjN = max(maxProjN, projN);
        }

        ld w = maxProjE - minProjE, h = maxProjN - minProjN;
        ld area = w * h;

        int cE = 0, cN = 0;
        for (const auto &p : pts) {
            ld projE = eDir.dot(p), projN = eNorm.dot(p);
            if (abs(projE - minProjE) < EPS || abs(projE - maxProjE) < EPS)
                cE++;
            if (abs(projN - minProjN) < EPS || abs(projN - maxProjN) < EPS)
                cN++;
        }
        if (cE >= 2 || cN >= 2) {
            minA = min(minA, area);
        }
    }

    return minA;
}

ld aARA(const set<ld> &xs, const set<ld> &ys, const map<ld, int> &xCnt, const map<ld, int> &yCnt) {
    ld minX = *xs.begin(), maxX = *xs.rbegin();
    ld minY = *ys.begin(), maxY = *ys.rbegin();
    ld area = (maxX - minX) * (maxY - minY);

    if (xCnt.at(minX) >= 2 || xCnt.at(maxX) >= 2 || yCnt.at(minY) >= 2 || yCnt.at(maxY) >= 2) {
        return area;
    }

    return numeric_limits<ld>::max();
}

int main() {
    freopen("fence.inp", "r", stdin);
    freopen("fence.out", "w", stdout);
    ios_base::sync_with_stdio(false);

    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<P> pts(n);
    set<ld> xs, ys;
    map<ld, int> xCnt, yCnt;
    
    for (int i = 0; i < n; ++i) {
        ld x, y;
        cin >> x >> y;
        pts[i] = P(x, y);
        xs.insert(x);
        ys.insert(y);
        xCnt[x]++;
        yCnt[y]++;
    }

    ld minA = aARA(xs, ys, xCnt, yCnt);

    vector<P> h = hull(pts);
    ld clrA = rCp(h, pts);

    minA = min(minA, clrA);

    cout << fixed << setprecision(12) << minA << endl;
    return 0;
}
