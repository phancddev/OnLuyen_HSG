#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

ll powmod(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

struct Matrix {
    int n;
    vector<vector<int>> adj;
    Matrix(int size){
        n = size;
        adj.assign(n+1, vector<int>());
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

struct Tree {
    int id;
    int diameter;
    int size;
    vector<int> height_counts;
};

struct IOManager {
    void read_int(int &x){
        cin >> x;
    }
    void write_int(ll x){
        cout << x << "\n";
    }
};

int main(){
    freopen("portal.inp", "r", stdin);
    freopen("portal.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    IOManager io;

    int n, m, Q;
    cin >> n >> m >> Q;

    Matrix matrix(n);
    for(int i=0;i<m;i++){
        int u, v;
        cin >> u >> v;
        matrix.add_edge(u, v);
    }

    vector<int> component_id(n+1, 0);
    vector<Tree> trees;
    int current_id = 0;

    vector<int> distance_temp(n+1, 0);

    auto bfs = [&](int start, vector<int> &dist, vector<int> &nodes) -> void {
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        nodes.push_back(start);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(auto &v : matrix.adj[u]){
                if(component_id[v]==0 && v != start){
                    component_id[v] = component_id[start];
                    dist[v] = dist[u] +1;
                    q.push(v);
                    nodes.push_back(v);
                }
            }
        }
    };

    for(int u=1; u<=n; u++){
        if(component_id[u]==0){
            current_id++;
            component_id[u] = current_id;
            vector<int> dist1(n+1, -1);
            queue<int> q1;
            q1.push(u);
            dist1[u] = 0;
            int furthest = u;
            while(!q1.empty()){
                int node = q1.front(); q1.pop();
                for(auto &v : matrix.adj[node]){
                    if(dist1[v]==-1){
                        dist1[v] = dist1[node] +1;
                        q1.push(v);
                        if(dist1[v] > dist1[furthest]){
                            furthest = v;
                        }
                    }
                }
            }
            vector<int> dist2(n+1, -1);
            queue<int> q2;
            q2.push(furthest);
            dist2[furthest] = 0;
            int furthest2 = furthest;
            while(!q2.empty()){
                int node = q2.front(); q2.pop();
                for(auto &v : matrix.adj[node]){
                    if(dist2[v]==-1){
                        dist2[v] = dist2[node] +1;
                        q2.push(v);
                        if(dist2[v] > dist2[furthest2]){
                            furthest2 = v;
                        }
                    }
                }
            }
            int diameter = dist2[furthest2];
            vector<int> dist_u(n+1, -1);
            queue<int> qu;
            qu.push(furthest);
            dist_u[furthest] = 0;
            while(!qu.empty()){
                int node = qu.front(); qu.pop();
                for(auto &v : matrix.adj[node]){
                    if(dist_u[v]==-1){
                        dist_u[v] = dist_u[node] +1;
                        qu.push(v);
                    }
                }
            }
            vector<int> dist_v(n+1, -1);
            queue<int> qv;
            qv.push(furthest2);
            dist_v[furthest2] = 0;
            while(!qv.empty()){
                int node = qv.front(); qv.pop();
                for(auto &v : matrix.adj[node]){
                    if(dist_v[v]==-1){
                        dist_v[v] = dist_v[node] +1;
                        qv.push(v);
                    }
                }
            }
            vector<int> height_counts_temp;
            int max_h = 0;
            vector<int> nodes;
            fill(distance_temp.begin(), distance_temp.end(), -1);
            queue<int> qc;
            qc.push(u);
            distance_temp[u] = 0;
            nodes.push_back(u);
            while(!qc.empty()){
                int node = qc.front(); qc.pop();
                for(auto &v : matrix.adj[node]){
                    if(distance_temp[v]==-1){
                        distance_temp[v] = distance_temp[node] +1;
                        qc.push(v);
                        nodes.push_back(v);
                        component_id[v] = current_id;
                    }
                }
            }
            height_counts_temp.assign(diameter +1, 0);
            for(auto &node : nodes){
                int h_a = max(dist_u[node], dist_v[node]);
                if(h_a >= (int)height_counts_temp.size()) height_counts_temp.resize(h_a +1, 0);
                height_counts_temp[h_a]++;
                if(h_a > max_h) max_h = h_a;
            }
            Tree tree;
            tree.id = current_id;
            tree.diameter = diameter;
            tree.size = nodes.size();
            tree.height_counts.assign(height_counts_temp.begin(), height_counts_temp.begin() + max_h +1);
            trees.push_back(tree);
        }
    }

    while(Q--){
        int u, v;
        cin >> u >> v;
        int cid1 = component_id[u];
        int cid2 = component_id[v];
        if(cid1 == cid2){
            io.write_int(-1);
            continue;
        }
        Tree &T1 = trees[cid1 -1];
        Tree &T2 = trees[cid2 -1];
        int D = max(T1.diameter, T2.diameter);
        vector<int> &c1 = T1.height_counts;
        vector<int> &c2 = T2.height_counts;
        int max_h2 = c2.size()-1;
        vector<ll> prefix_sum_c2(max_h2 +2, 0);
        vector<ll> prefix_sum_h2c2(max_h2 +2, 0);
        for(int h=0; h<=max_h2; h++){
            prefix_sum_c2[h+1] = prefix_sum_c2[h] + c2[h];
            prefix_sum_h2c2[h+1] = prefix_sum_h2c2[h] + ((ll)h * c2[h]);
        }
        ll sum2 =0;
        for(int h1=0; h1 < (int)c1.size(); h1++){
            int t = D - h1;
            if(t <0) t =0;
            if(t > max_h2) continue;
            ll sum_c2_ge_t = prefix_sum_c2[max_h2 +1] - prefix_sum_c2[t];
            ll sum_h2_ge_t = prefix_sum_h2c2[max_h2 +1] - prefix_sum_h2c2[t];
            ll term1 = ((ll)(h1 +1 - D)) * sum_c2_ge_t;
            ll term2 = sum_h2_ge_t;
            sum2 = (sum2 + (c1[h1] * (term1 + term2))%MOD)%MOD;
        }
        ll P = (( (ll)D * T1.size) % MOD * T2.size) % MOD;
        P = (P + sum2) % MOD;
        ll Q_val = ((ll)T1.size * T2.size) % MOD;
        ll Q_inv = powmod(Q_val, MOD-2, MOD);
        ll res = (P * Q_inv) % MOD;
        io.write_int(res);
    }

    return 0;
}
