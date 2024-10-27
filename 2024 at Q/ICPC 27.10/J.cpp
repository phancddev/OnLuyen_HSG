#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

struct Matrix {
    int size;
    vector<vector<Edge>> adj;
    Matrix(int n) : size(n), adj(n, vector<Edge>()) {}

    void add_edge(int from, int to, int cap) {
        Edge a = {to, (int)adj[to].size(), cap};
        Edge b = {from, (int)(adj[from].size()), 0};
        adj[from].push_back(a);
        adj[to].push_back(b);
    }

    int max_flow(int s, int t) {
        vector<int> level(size, -1);
        vector<int> ptr(size, 0);
        int flow = 0;

        auto bfs = [&](int s, int t, vector<int>& level) -> bool {
            fill(level.begin(), level.end(), -1);
            queue<int> q;
            q.push(s);
            level[s] = 0;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                for(auto &e : adj[u]) {
                    if(e.cap > 0 && level[e.to] == -1){
                        level[e.to] = level[u] +1;
                        q.push(e.to);
                        if(e.to == t) return true;
                    }
                }
            }
            return level[t] != -1;
        };

        function<int(int, int, int)> dfs = [&](int u, int t, int pushed) -> int {
            if(u == t) return pushed;
            for(int &cid = ptr[u]; cid < adj[u].size(); cid++) {
                Edge &e = adj[u][cid];
                if(e.cap > 0 && level[e.to] == level[u] +1){
                    int tr = dfs(e.to, t, min(pushed, e.cap));
                    if(tr >0){
                        adj[u][cid].cap -= tr;
                        adj[e.to][e.rev].cap += tr;
                        return tr;
                    }
                }
            }
            return 0;
        };

        while(bfs(s, t, level)){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(s, t, INT32_MAX)){
                flow += pushed;
            }
        }
        return flow;
    }
};

struct IOManager {
    int L, W, N;
    vector<pair<int, int>> sensors;

    void read_input(){
        ios::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        cin >> L >> W >> N;
        sensors.resize(N);
        for(int i=0; i<N; i++){
            cin >> sensors[i].first >> sensors[i].second;
        }
    }

    void write_output(long long result){
        cout << result;
    }
};

int main(){
    IOManager io;
    io.read_input();
    int N = io.N;
    int L = io.L;
    int W = io.W;
    int total_nodes = 2*N + 2;
    int top = 2*N;
    int bottom = 2*N +1;

    Matrix graph(total_nodes);

    for(int i=0; i<N; i++){
        int i_in = i;
        int i_out = i + N;
        graph.add_edge(i_in, i_out, 1);
    }

    auto distance_sq = [&](int i, int j) -> long long {
        long long dx = (long long)(io.sensors[i].first - io.sensors[j].first);
        long long dy = (long long)(io.sensors[i].second - io.sensors[j].second);
        return dx*dx + dy*dy;
    };

    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(distance_sq(i, j) <= 40000LL){
                int i_out = i + N;
                int j_in = j;
                graph.add_edge(i_out, j_in, N+1);
                int j_out = j + N;
                int i_in = i;
                graph.add_edge(j_out, i_in, N+1);
            }
        }
    }

    for(int i=0; i<N; i++){
        int y = io.sensors[i].second;
        if(y - 100 <= 0){
            int i_in = i;
            graph.add_edge(top, i_in, N+1);
        }
        if(y + 100 >= W){
            int i_out = i + N;
            graph.add_edge(i_out, bottom, N+1);
        }
    }

    int flow = graph.max_flow(top, bottom);

    if(flow ==0){
        io.write_output(0);
    }
    else{
        io.write_output((long long)flow);
    }
}
