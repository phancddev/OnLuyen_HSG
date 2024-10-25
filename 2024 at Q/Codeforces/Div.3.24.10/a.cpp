#include <bits/stdc++.h>
using namespace std;
struct MatrixManager {
    vector<vector<int>> positions;
    MatrixManager(int maxN) {
        positions.resize(maxN + 1);
        for (int n = 1; n <= maxN; ++n) {
            int x = 0;
            int i = 1;
            while (true) {
                int move = (2 * i - 1);
                if (i % 2 == 1) move = -move;
                int next_x = x + move;
                positions[n].push_back(next_x);
                if (abs(next_x) > n) break;
                x = next_x;
                ++i;
            }
        }
    }
};
struct InputOutputManager {
    vector<int> ns;
    void read_input(int t) {
        ns.resize(t);
        for (int i = 0; i < t; ++i) cin >> ns[i];
    }
    void write_output(const vector<string>& results) {
        for (const string& res : results) cout << res << '\n';
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    InputOutputManager io;
    io.read_input(t);
    MatrixManager matrix(100);
    vector<string> results;
    for (int n : io.ns) {
        int moves = matrix.positions[n].size();
        string winner = (moves % 2 == 1) ? "Sakurako" : "Kosuke";
        results.push_back(winner);
    }
    io.write_output(results);
    return 0;
}