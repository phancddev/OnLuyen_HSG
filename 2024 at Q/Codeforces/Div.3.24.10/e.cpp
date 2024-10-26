#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int rows;
    int cols;
    vector<vector<int>> data;

    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}

    void populateFromArray(const vector<int>& arr) {
        for(int i = 0; i < arr.size(); ++i) {
            if(cols == 1) {
                data[0][0] = arr[i];
            } else {
                data[0][i] = arr[i];
            }
        }
    }

    void display() const {
        for(const auto& row : data) {
            for(const auto& elem : row) {
                cout << elem << ' ';
            }
            cout << '\n';
        }
    }
};

struct IOManager {
    void readTestCase(int& n, vector<int>& arr) const {
        cin >> n;
        arr.resize(n);
        for(auto &x : arr) cin >> x;
    }

    void writeResult(int result) const {
        cout << result << '\n';
    }
};

int minSwapsToSimplePermutation(const vector<int>& arr) {
    int n = arr.size();
    vector<bool> visited(n, false);
    int totalSwaps = 0;

    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        p[i] = arr[i] -1;
    }

    for(int i = 0; i < n; ++i) {
        if(!visited[i]) {
            int cycle_length = 0;
            int j = i;
            while(!visited[j]) {
                visited[j] = true;
                j = p[j];
                cycle_length++;
            }
            if(cycle_length >= 3) {
                totalSwaps += floor((cycle_length - 1) / 2);
            }
        }
    }

    return totalSwaps;
}
//sweetie.zz E
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    IOManager io;
    int t;
    cin >> t;
    while(t--) {
        int n;
        vector<int> arr;
        io.readTestCase(n, arr);

        Matrix matrix(1, n);
        matrix.populateFromArray(arr);

        int result = minSwapsToSimplePermutation(arr);
        io.writeResult(result);
    }
    return 0;
}
