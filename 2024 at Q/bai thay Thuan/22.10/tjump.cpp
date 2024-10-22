#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Matrix {
    vector<int> data;
    int rows, cols;

    Matrix(int n) : rows(1), cols(n) {
        data.resize(n + 1);
    }

    int& operator()(int i) {
        return data[i];
    }
};

struct Query {
    int L, R;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("tjump.inp", "r", stdin);
    freopen("tjump.out", "w", stdout);
    int N;
    cin >> N;
    Matrix A(N);
    for (int i = 1; i <= N; ++i) {
        cin >> A(i);
    }

    int Q;
    cin >> Q;
    vector<Query> queries(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> queries[i].L >> queries[i].R;
    }

    const int K = 30;
    for (const auto& query : queries) {
        int L = query.L;
        int R = query.R;

        vector<pair<int, int> > elements;
        for (int i = L; i <= R; ++i) {
            elements.emplace_back(A(i), i);
        }

        sort(elements.rbegin(), elements.rend());

        int limit = min(K, (int)elements.size());
        vector<int> indices;
        for (int i = 0; i < limit; ++i) {
            indices.push_back(elements[i].second);
        }

        sort(indices.begin(), indices.end());

        long long max_strength = 0;

        for (size_t i = 0; i < indices.size(); ++i) {
            for (size_t j = i + 1; j < indices.size(); ++j) {
                for (size_t k = j + 1; k < indices.size(); ++k) {
                    int a = indices[i];
                    int b = indices[j];
                    int c = indices[k];
                    if (a < b && b < c && (b - a) <= (c - b)) {
                        long long current_strength = A(a) + A(b) + A(c);
                        if (current_strength > max_strength) {
                            max_strength = current_strength;
                        }
                    }
                }
            }
        }

        cout << max_strength << '\n';
    }

    return 0;
}
