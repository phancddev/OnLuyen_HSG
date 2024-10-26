#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n;
    vector<vector<pair<int, long long>>> adj;
    Matrix(int nodes) : n(nodes), adj(nodes + 1, vector<pair<int, long long>>()) {}
    void add_edge(int u, int v, long long w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
};

struct IOManager {
    int n, m, k, T;
    vector<int> customer_pos;
    struct Edge {
        int u, v;
        long long w;
    };
    vector<Edge> edges;
    void read_input() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        cin >> n >> m >> k >> T;
        customer_pos.resize(k);
        for(auto &x : customer_pos) cin >> x;
        for(int i = 0; i < m; ++i) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            bool found = false;
            for(auto &e : edges) {
                if((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
                    if(w < e.w) {
                        e.w = w;
                    }
                    found = true;
                    break;
                }
            }
            if(!found) {
                edges.push_back(Edge{u, v, w});
            }
        }
    }
};

struct Solution {
    long long total_cost;
    int num_trips;
    struct Trip {
        string mask;
        int u;
        int v;
    };
    vector<Trip> trips;
    void output_solution() {
        cout << total_cost << "\n";
        cout << num_trips << "\n";
        for(auto &trip : trips) {
            cout << trip.mask << " " << trip.u << " " << trip.v << "\n";
        }
    }
};

string get_mask_str(int mask, int k) {
    string s = "";
    for(int i = k - 1; i >= 0; i--) {
        if(mask & (1 << i)) s += '1';
        else s += '0';
    }
    return s;
}

int main() {
    freopen("TAXI.inp", "r", stdin);
    freopen("TAXI.out", "w", stdout);
    IOManager io;
    io.read_input();
    Matrix city(io.n);
    for(auto &e : io.edges) {
        city.add_edge(e.u, e.v, e.w);
    }
    int T = io.T;
    const long long INF = 1e18;
    vector<long long> dist(io.n + 1, INF);
    vector<int> parent(io.n + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, std::greater<pair<long long, int>>> pq;
    dist[T] = 0;
    parent[T] = T;
    pq.emplace(0, T);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto &[v, w] : city.adj[u]) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    vector<int> customer_order(io.k);
    for(int i = 0; i < io.k; i++) customer_order[i] = i;
    sort(customer_order.begin(), customer_order.end(), [&](const int a, const int b) -> bool {
        return io.customer_pos[a] > io.customer_pos[b];
    });
    struct EdgeInfo {
        int u;
        int v;
        long long w;
        int mask;
    };
    vector<vector<EdgeInfo>> customer_paths(io.k, vector<EdgeInfo>());
    for(int i = 0; i < io.k; i++) {
        int pos = io.customer_pos[i];
        if(pos == T) {
            continue;
        }
        int current = pos;
        while(current != T) {
            int p = parent[current];
            if(p == -1) {
                break;
            }
            long long w = 0;
            for(auto &[v, wgt] : city.adj[current]) {
                if(v == p) {
                    w = wgt;
                    break;
                }
            }
            customer_paths[i].push_back(EdgeInfo{current, p, w, (1 << (io.k - 1 - i))});
            current = p;
        }
    }
    int max_steps = 0;
    for(int i = 0; i < io.k; i++) {
        max_steps = max(max_steps, (int)customer_paths[i].size());
    }
    Solution sol;
    sol.total_cost = 0;
    sol.trips.reserve(io.k * max_steps);
    map<pair<int, int>, int> edge_map;
    for(int step = 0; step < max_steps; step++) {
        for(auto customer_id : customer_order) {
            if(step < customer_paths[customer_id].size()) {
                EdgeInfo e = customer_paths[customer_id][step];
                int u = min(e.u, e.v);
                int v = max(e.u, e.v);
                pair<int, int> edge = make_pair(u, v);
                if(edge_map.find(edge) == edge_map.end()) {
                    string mask_str = get_mask_str(e.mask, io.k);
                    sol.trips.push_back(Solution::Trip{mask_str, e.u, e.v});
                    edge_map[edge] = sol.trips.size() - 1;
                    sol.total_cost += e.w;
                } else {
                    int idx = edge_map[edge];
                    int existing_mask = 0;
                    for(int bit = 0; bit < io.k; bit++) {
                        if(sol.trips[idx].mask[bit] == '1') {
                            existing_mask |= (1 << (io.k - 1 - bit));
                        }
                    }
                    existing_mask |= e.mask;
                    sol.trips[idx].mask = get_mask_str(existing_mask, io.k);
                }
            }
        }
    }
    sol.num_trips = sol.trips.size();
    sol.output_solution();
}
