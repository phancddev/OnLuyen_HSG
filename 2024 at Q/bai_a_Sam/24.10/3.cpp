#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int LOGN = 20;

struct Edge {
    int u, v;
    int64_t w;
    int idx;
    bool in_mst;
};

int n, m;
int parent[MAXN][LOGN];
int64_t maxEdge[MAXN][LOGN];
int depth[MAXN];
vector<pair<int, int64_t>> adj[MAXN];
vector<Edge> edges;
int64_t Wmst = 0;

int find_set(vector<int>& dsu_parent, int u) {
    if (dsu_parent[u] != u)
        dsu_parent[u] = find_set(dsu_parent, dsu_parent[u]);
    return dsu_parent[u];
}

void union_sets(vector<int>& dsu_parent, vector<int>& dsu_rank, int u, int v) {
    u = find_set(dsu_parent, u);
    v = find_set(dsu_parent, v);
    if (u != v) {
        if (dsu_rank[u] < dsu_rank[v])
            swap(u, v);
        dsu_parent[v] = u;
        if (dsu_rank[u] == dsu_rank[v])
            dsu_rank[u]++;
    }
}

void dfs(int u, int p) {
    for (auto& [v, w] : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            maxEdge[v][0] = w;
            dfs(v, u);
        }
    }
}

void build_lca() {
    for (int k = 1; k < LOGN; ++k) {
        for (int u = 1; u <= n; ++u) {
            int anc = parent[u][k - 1];
            parent[u][k] = parent[anc][k - 1];
            maxEdge[u][k] = max(maxEdge[u][k - 1], maxEdge[anc][k - 1]);
        }
    }
}

int64_t query_max_edge(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    int64_t res = 0;
    for (int k = LOGN - 1; k >= 0; --k) {
        if (depth[u] - (1 << k) >= depth[v]) {
            res = max(res, maxEdge[u][k]);
            u = parent[u][k];
        }
    }
    if (u == v)
        return res;
    for (int k = LOGN - 1; k >= 0; --k) {
        if (parent[u][k] != parent[v][k]) {
            res = max({res, maxEdge[u][k], maxEdge[v][k]});
            u = parent[u][k];
            v = parent[v][k];
        }
    }
    res = max({res, maxEdge[u][0], maxEdge[v][0]});
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        Edge& e = edges[i];
        cin >> e.u >> e.v >> e.w;
        e.idx = i;
        e.in_mst = false;
    }

    vector<int> dsu_parent(n + 1), dsu_rank(n + 1, 0);
    iota(dsu_parent.begin(), dsu_parent.end(), 0);
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    for (Edge& e : edges) {
        int u_root = find_set(dsu_parent, e.u);
        int v_root = find_set(dsu_parent, e.v);
        if (u_root != v_root) {
            e.in_mst = true;
            Wmst += e.w;
            union_sets(dsu_parent, dsu_rank, e.u, e.v);
            adj[e.u].emplace_back(e.v, e.w);
            adj[e.v].emplace_back(e.u, e.w);
        }
    }

    depth[1] = 0;
    parent[1][0] = 0;
    maxEdge[1][0] = 0;
    dfs(1, 0);
    build_lca();

    vector<int64_t> ans(m);
    for (const Edge& e : edges) {
        if (e.in_mst) {
            ans[e.idx] = Wmst;
        } else {
            int64_t wmax = query_max_edge(e.u, e.v);
            ans[e.idx] = Wmst + e.w - wmax;
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << ans[i] << '\n';
    }

    return 0;
}
