#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct IOManager {
    static const int S = 1 << 20;
    char inbuf[S];
    int inpos, inlen;
    char outbuf[S];
    int outpos;
    
    IOManager() : inpos(0), inlen(0), outpos(0) {}
    
    char getChar() {
        if (inpos == inlen) {
            inlen = fread(inbuf, 1, S, stdin);
            inpos = 0;
            if (inlen == 0) return EOF;
        }
        return inbuf[inpos++];
    }
    
    bool readInt(int &x) {
        char c;
        x = 0;
        bool neg = false;
        while ((c = getChar()) && !isdigit(c)) {
            if (c == '-') neg = true;
            if (c == EOF) return false;
        }
        do {
            x = x * 10 + (c - '0');
        } while ((c = getChar()) && isdigit(c));
        if (neg) x = -x;
        return true;
    }
    
    void writeInt(int x) {
        if (outpos > S - 20) flush();
        if (x == 0) {
            outbuf[outpos++] = '0';
            outbuf[outpos++] = '\n';
            return;
        }
        if (x < 0) {
            outbuf[outpos++] = '-';
            x = -x;
        }
        char tmp[20];
        int len = 0;
        while (x > 0) {
            tmp[len++] = '0' + (x % 10);
            x /= 10;
        }
        for (int i = len - 1; i >= 0; --i) outbuf[outpos++] = tmp[i];
        outbuf[outpos++] = '\n';
    }
    
    void writeChar(char c) {
        if (outpos == S) flush();
        outbuf[outpos++] = c;
    }
    
    void flush() {
        fwrite(outbuf, 1, outpos, stdout);
        outpos = 0;
    }
    
    ~IOManager() {
        flush();
    }
};

struct seg_tree_node {
    int l, r;
    ll mask;
    int lazy;
};

const int MAX = 200005;
const int LOG = 20;

int n, q;
vector<vector<int>> adj(MAX);
int in_time[MAX], out_time[MAX];
int timer_dfs = 0;
int parent_node[MAX][LOG];
int depth_node[MAX];
int initial_color[MAX];

struct SegmentTree {
    int size;
    vector<seg_tree_node> tree;
    
    SegmentTree(int n) {
        size = 1;
        while (size < n) size <<=1;
        tree.assign(2*size, seg_tree_node());
        for(int i=0;i<2*size;i++) tree[i].lazy = -1;
    }
    
    void build(vector<int> &colors, int node, int l, int r){
        tree[node].l = l;
        tree[node].r = r;
        tree[node].lazy = -1;
        if(l == r){
            tree[node].mask = 1LL << (colors[l] - 1);
            return;
        }
        int mid = (l + r) / 2;
        build(colors, 2*node, l, mid);
        build(colors, 2*node+1, mid+1, r);
        tree[node].mask = tree[2*node].mask | tree[2*node+1].mask;
    }
    
    void push_down(int node){
        if(tree[node].lazy != -1){
            ll new_mask = 1LL << (tree[node].lazy - 1);
            tree[2*node].mask = new_mask;
            tree[2*node].lazy = tree[node].lazy;
            tree[2*node+1].mask = new_mask;
            tree[2*node+1].lazy = tree[node].lazy;
            tree[node].lazy = -1;
        }
    }
    
    void update_range(int node, int l, int r, int x){
        if(r < tree[node].l || l > tree[node].r) return;
        if(l <= tree[node].l && tree[node].r <= r){
            tree[node].mask = 1LL << (x - 1);
            tree[node].lazy = x;
            return;
        }
        push_down(node);
        update_range(2*node, l, r, x);
        update_range(2*node+1, l, r, x);
        tree[node].mask = tree[2*node].mask | tree[2*node+1].mask;
    }
    
    ll query_range(int node, int l, int r){
        if(r < tree[node].l || l > tree[node].r) return 0;
        if(l <= tree[node].l && tree[node].r <= r){
            return tree[node].mask;
        }
        push_down(node);
        return query_range(2*node, l, r) | query_range(2*node+1, l, r);
    }
};

void dfs(int u, int p) {
    in_time[u] = ++timer_dfs;
    parent_node[u][0] = p;
    for(int i=1;i<LOG;i++) {
        parent_node[u][i] = parent_node[parent_node[u][i-1]][i-1];
    }
    for(auto &v: adj[u]) {
        if(v != p){
            depth_node[v] = depth_node[u] + 1;
            dfs(v, u);
        }
    }
    out_time[u] = timer_dfs;
}

int lca_func(int u, int v){
    if(depth_node[u] < depth_node[v]) swap(u, v);
    for(int k=LOG-1; k>=0; k--){
        if(depth_node[u] - (1<<k) >= depth_node[v]){
            u = parent_node[u][k];
        }
    }
    if(u == v) return u;
    for(int k=LOG-1; k>=0; k--){
        if(parent_node[u][k] != parent_node[v][k]){
            u = parent_node[u][k];
            v = parent_node[v][k];
        }
    }
    return parent_node[u][0];
}

void update_path(int u, int v, int x, SegmentTree &seg) {
    int lca = lca_func(u, v);
    while(u != lca){
        seg.update_range(1, in_time[u], in_time[u], x);
        u = parent_node[u][0];
    }
    while(v != lca){
        seg.update_range(1, in_time[v], in_time[v], x);
        v = parent_node[v][0];
    }
    seg.update_range(1, in_time[lca], in_time[lca], x);
}

ll query_path(int u, int v, SegmentTree &seg) {
    int lca = lca_func(u, v);
    ll res = 0;
    while(u != lca){
        res |= seg.query_range(1, in_time[u], in_time[u]);
        u = parent_node[u][0];
    }
    while(v != lca){
        res |= seg.query_range(1, in_time[v], in_time[v]);
        v = parent_node[v][0];
    }
    res |= seg.query_range(1, in_time[lca], in_time[lca]);
    return res;
}

int main(){
    IOManager io;
    io.readInt(n);
    io.readInt(q);
    for(int i=1;i<n;i++){
        int u, v;
        io.readInt(u);
        io.readInt(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> temp_color(n+1);
    for(int i=1;i<=n;i++) io.readInt(temp_color[i]);
    dfs(1,1);
    vector<int> euler_color(n+1);
    for(int i=1;i<=n;i++) euler_color[in_time[i]] = temp_color[i];
    SegmentTree seg_tree(n);
    seg_tree.build(euler_color, 1, 1, n);
    while(q--){
        int type;
        io.readInt(type);
        if(type == 1){
            int u, v, x;
            io.readInt(u);
            io.readInt(v);
            io.readInt(x);
            update_path(u, v, x, seg_tree);
        }
        else if(type == 2){
            int u, x;
            io.readInt(u);
            io.readInt(x);
            seg_tree.update_range(1, in_time[u], out_time[u], x);
        }
        else if(type == 3){
            int u, v;
            io.readInt(u);
            io.readInt(v);
            ll res = query_path(u, v, seg_tree);
            int cnt = __builtin_popcountll(res);
            io.writeInt(cnt);
        }
        else if(type == 4){
            int u;
            io.readInt(u);
            ll res = seg_tree.query_range(1, in_time[u], out_time[u]);
            int cnt = __builtin_popcountll(res);
            io.writeInt(cnt);
        }
    }
    return 0;
}
