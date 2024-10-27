#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int n;
    vector<int> a;

    Matrix(int size, const vector<int> &array) : n(size), a(array) {}

    int countGreater(int i) const {
        int cnt = 0;
        for(int j = i + 1; j < n; j++) {
            if(a[j] > a[i]) cnt++;
        }
        return cnt;
    }
};

struct IOManager {
    void readInput(int &t, vector<Matrix> &testCases){
        cin >> t;
        for(int i = 0; i < t; i++){
            int n;
            cin >> n;
            vector<int> a(n);
            for(int j = 0; j < n; j++) cin >> a[j];
            testCases.emplace_back(n, a);
        }
    }

    void outputResults(const vector<int> &results){
        for(auto res : results){
            cout << res << "\n";
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    IOManager io;
    vector<Matrix> testCases;
    io.readInput(t, testCases);

    vector<int> results;

    for(auto &testCase : testCases){
        int n = testCase.n;
        int ans = INT32_MAX;

        for(int i = 0; i < n; i++){
            int deletions_before = i;
            int deletions_after = testCase.countGreater(i);
            int total_deletions = deletions_before + deletions_after;
            ans = min(ans, total_deletions);
        }

        results.push_back(ans);
    }

    io.outputResults(results);
}
