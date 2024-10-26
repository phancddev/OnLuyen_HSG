#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
const ll INF = 1e18 + 7;
const int N = 1002;

struct IOManager {
    int n, m;
    vector<vector<char>> board;
    vector<vector<ll>> points;

    void read_input() {
        cin >> n >> m;
        board.resize(n + 2, vector<char>(m + 2, 'x'));
        points.resize(n + 2, vector<ll>(m + 2, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> board[i][j];
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> points[i][j];
            }
        }
    }

    void write_output(ll result) {
        cout << result << "\n";
    }
};

struct Grid {
    int n, m;
    vector<vector<char>> cells;
    vector<vector<ll>> values;
    vector<vector<bool>> visited;

    Grid(int n, int m, const vector<vector<char>>& board, const vector<vector<ll>>& points) 
        : n(n), m(m), cells(board), values(points) {
        visited.resize(n + 2, vector<bool>(m + 2, false));
    }

    ll dfs(int x, int y) {
        if (visited[x][y]) return 0;
        visited[x][y] = true;

        ll res = values[x][y];
        if (cells[x][y + 1] == 'H') {
            ll tmp = dfs(x, y + 2);
            if (tmp > 0) res += tmp;
        }
        if (cells[x][y - 1] == '.' && cells[x][y - 2] == 'H') {
            ll tmp = dfs(x, y - 2);
            if (tmp > 0) res += tmp;
        }
        if (cells[x - 1][y] == '.' && cells[x - 2][y] == 'V') {
            ll tmp = dfs(x - 2, y);
            if (tmp > 0) res += tmp;
        }
        if (cells[x + 1][y] == 'V') {
            ll tmp = dfs(x + 2, y);
            if (tmp > 0) res += tmp;
        }
        return res;
    }

    ll solve() {
        ll total = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (cells[i][j] == 'O') {
                    total += dfs(i, j);
                }
            }
        }
        return total;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("unblock.inp", "r", stdin);
    freopen("unblock.out", "w", stdout);

    IOManager io;
    io.read_input();

    Grid grid(io.n, io.m, io.board, io.points);
    ll result = grid.solve();

    io.write_output(result);

    return 0;
}
