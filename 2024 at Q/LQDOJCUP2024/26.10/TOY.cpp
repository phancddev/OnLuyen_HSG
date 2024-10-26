#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Matrix {
    int n;
    vector<ll> a;
    vector<ll> seg;

    Matrix(int size) : n(size), a(size + 1, 0), seg(4 * size, 0) {}

    void build(int node, int l, int r) {
        if(l == r){
            seg[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        seg[node] = seg[2*node] + seg[2*node+1];
    }

    void update(int node, int l, int r, int idx, ll val){
        if(l == r){
            seg[node] = val;
            a[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if(idx <= mid)
            update(2*node, l, mid, idx, val);
        else
            update(2*node+1, mid+1, r, idx, val);
        seg[node] = seg[2*node] + seg[2*node+1];
    }

    ll query(int node, int l, int r, int L, int R){
        if(R < l || L > r)
            return 0;
        if(L <= l && r <= R)
            return seg[node];
        int mid = (l + r) / 2;
        return query(2*node, l, mid, L, R) + query(2*node+1, mid+1, r, L, R);
    }
};

struct IOManager {
    void inputData(int &n, int &q, Matrix &matrix){
        cin >> n >> q;
        for(int i=1; i<=n; ++i){
            cin >> matrix.a[i];
        }
        matrix.build(1, 1, n);
    }

    void processEvents(int q, Matrix &matrix){
        while(q--){
            int type;
            cin >> type;
            if(type == 1){
                int i;
                ll x;
                cin >> i >> x;
                matrix.update(1, 1, matrix.n, i, x);
            }
            else if(type == 2){
                int l, r;
                cin >> l >> r;
                ll total = matrix.query(1, 1, matrix.n, l, r);
                int low = l, high = r-1, best = l;
                ll minDiff = LLONG_MAX;
                while(low <= high){
                    int mid = low + (high - low) / 2;
                    ll sum1 = matrix.query(1, 1, matrix.n, l, mid);
                    ll sum2 = total - sum1;
                    ll diff = abs(sum1 - sum2);
                    if(diff < minDiff){
                        minDiff = diff;
                        best = mid;
                    }
                    if(sum1 < sum2)
                        low = mid + 1;
                    else
                        high = mid - 1;
                }
                cout << minDiff << "\n";
            }
        }
    }
};

struct ToyStore {
    Matrix *matrix;
    IOManager io;

    void initialize(int n){
        matrix = new Matrix(n);
    }

    void input(){
        int n, q;
        io.inputData(n, q, *matrix);
        io.processEvents(q, *matrix);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("TOY.inp", "r", stdin);
    freopen("TOY.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    ToyStore store;
    store.initialize(n);
    for(int i=1; i<=n; ++i){
        cin >> store.matrix->a[i];
    }
    store.matrix->build(1, 1, n);
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int i;
            ll x;
            cin >> i >> x;
            store.matrix->update(1, 1, store.matrix->n, i, x);
        }
        else if(type == 2){
            int l, r;
            cin >> l >> r;
            ll total = store.matrix->query(1, 1, store.matrix->n, l, r);
            int low = l, high = r-1, best = l;
            ll minDiff = LLONG_MAX;
            while(low <= high){
                int mid = low + (high - low) / 2;
                ll sum1 = store.matrix->query(1, 1, store.matrix->n, l, mid);
                ll sum2 = total - sum1;
                ll diff = abs(sum1 - sum2);
                if(diff < minDiff){
                    minDiff = diff;
                    best = mid;
                }
                if(sum1 < sum2)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            cout << minDiff << "\n";
        }
    }
}
