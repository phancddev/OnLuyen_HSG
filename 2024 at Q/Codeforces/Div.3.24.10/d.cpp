
//hacked 
#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int r;
    int c;
    vector<vector<int>> d;

    Matrix(int r, int c) : r(r), c(c), d(r, vector<int>(c, 0)) {}

    void populateFromArray(const vector<int>& arr) {
        for(int i = 0; i < arr.size(); ++i) {
            if(c == 1) {
                d[0][0] = arr[i];
            } else {
                d[0][i] = arr[i];
            }
        }
    }
};

struct IOManager {
    void read(int& n, vector<int>& arr) const {
        cin >> n;
        arr.resize(n);
        for(auto &x : arr) cin >> x;
    }

    void writeResult(int res) const {
        cout << res << '\n';
    }
};

int maxZeroSumSegments(const vector<int>& arr) {
    unordered_map<long long, int> pSumMap;
    pSumMap[0] = -1;

    long long pSum = 0;
    int cnt = 0;
    int lastEnd = -1;

    for(int i = 0; i < arr.size(); ++i) {
        pSum += arr[i];

        if(pSumMap.find(pSum) != pSumMap.end()) {
            int prevIdx = pSumMap[pSum];
            if(prevIdx >= lastEnd) {
                cnt++;
                lastEnd = i;
            }
        }

        pSumMap[pSum] = i;
    }

    return cnt;
}
//sweetie.zz
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    IOManager io;
    int t;
    cin >> t;
    while(t--){
        int n;
        vector<int> arr;
        io.read(n, arr);

        Matrix mtx(1, n);
        mtx.populateFromArray(arr);

        int res = maxZeroSumSegments(arr);
        io.writeResult(res);
    }
    return 0;
}




