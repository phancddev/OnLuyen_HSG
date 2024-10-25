#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n;
    vector<vector<int>> a;
    Matrix(int n): n(n), a(n, vector<int>(n)) {}
};

struct IOManager {
    vector<Matrix> matrices;
    void read_input() {
        int t;
        cin >> t;
        for (int k = 0; k < t; ++k) {
            int n;
            cin >> n;
            Matrix matrix(n);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    cin >> matrix.a[i][j];
            matrices.push_back(matrix);
        }
    }
    void write_output(const vector<long long>& results) {
        for (auto res : results)
            cout << res << '\n';
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    IOManager io;
    io.read_input();
    vector<long long> results;
    for (auto& matrix : io.matrices) {
        int n = matrix.n;
        vector<vector<long long>> sum(n + 1, vector<long long>(n + 1, 0));
        long long total_operations = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                long long delta = sum[i + 1][j + 1];
                long long current_value = matrix.a[i][j] + delta;
                if (current_value < 0) {
                    long long need = -current_value;
                    total_operations += need;
                    sum[i][j] = sum[i + 1][j + 1] + need;
                } else {
                    sum[i][j] = sum[i + 1][j + 1];
                }
            }
        }
        results.push_back(total_operations);
    }
    io.write_output(results);
    return 0;
}