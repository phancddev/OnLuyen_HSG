#include <bits/stdc++.h>
using namespace std;

struct OperationMapping {
    long long value;
    int index;

    bool operator<(const OperationMapping& other) const {
        return value < other.value;
    }
};

struct IOManager {
    void readTestCase(int& n, vector<long long>& a) {
        cin >> n;
        a.resize(n);
        for(auto &x : a) cin >> x;
    }

    void writeResult(long long result) {
        cout << result << "\n";
    }
};

long long computeMaxL(int n, const vector<long long>& a) {
    vector<OperationMapping> sorted_ops;
    sorted_ops.reserve(n);
    for(int j = 0; j < n; ++j){
        sorted_ops.push_back(OperationMapping{a[j] + (j +1), j+1});
    }
    sort(sorted_ops.begin(), sorted_ops.end());

    vector<vector<int>> next_ops(n+1, vector<int>());
    for(int i =1; i<=n; ++i){
        long long target = a[i-1] + 2LL*(i-1) +1;
        OperationMapping key;
        key.value = target;
        key.index = 0;
        auto it_low = lower_bound(sorted_ops.begin(), sorted_ops.end(), key);
        key.value = target;
        auto it_up = upper_bound(sorted_ops.begin(), sorted_ops.end(), key);
        for(auto it = it_low; it != it_up; ++it){
            if(it->index != i){
                next_ops[i].push_back(it->index);
            }
        }
    }

    vector<int> initial_ops;
    for(int i=1; i<=n; ++i){
        if(a[i-1] + (i) -1 == n){
            initial_ops.push_back(i);
        }
    }

    vector<long long> max_L(n+1, -1);
    vector<bool> visited(n+1, false);

    for(auto i : initial_ops){
        if(max_L[i] != -1) continue;
        stack<int> stk;
        stk.push(i);
        vector<int> path;
        while(!stk.empty()){
            int node = stk.top();
            stk.pop();
            if(visited[node]){
                continue;
            }
            visited[node] = true;
            path.push_back(node);
            for(auto &j : next_ops[node]){
                if(!visited[j]){
                    stk.push(j);
                }
            }
        }
        for(auto it = path.rbegin(); it != path.rend(); ++it){
            int node = *it;
            long long current_L = a[node-1] + 2LL*(node -1);
            for(auto &j : next_ops[node]){
                current_L = max(current_L, max_L[j]);
            }
            max_L[node] = current_L;
        }
    }

    long long answer = n;
    for(auto i : initial_ops){
        answer = max(answer, max_L[i]);
    }
    return answer;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    IOManager io;
    int t;
    cin >> t;
    while(t--){
        int n;
        vector<long long> a;
        io.readTestCase(n, a);
        long long result = computeMaxL(n, a);
        io.writeResult(result);
    }
}
