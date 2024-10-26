#include <bits/stdc++.h>
using namespace std;

struct Project {
    int id;
    long long b_i;
    int q_i;
    vector<int> children;
};

struct Matrix {
    int n;
    vector<Project> projects;

    Matrix(int size) : n(size), projects(size + 1) {
        for(int i=1;i<=n;i++) {
            projects[i].id = i;
        }
    }
};

struct IOManager {
    void readInput(Matrix &matrix){
        for(int i=1;i<=matrix.n;i++){
            cin >> matrix.projects[i].b_i >> matrix.projects[i].q_i;
            if(matrix.projects[i].q_i !=0){
                matrix.projects[matrix.projects[i].q_i].children.push_back(i);
            }
        }
    }

    void writeOutput(long long profit){
        cout << profit;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    long long u;
    cin >> n >> u;
    Matrix matrix(n);
    IOManager io;
    io.readInput(matrix);

    vector<bool> required(n+1, false);
    stack<int> stk;
    for(int i=1;i<=n;i++){
        if(matrix.projects[i].b_i >=0 && !required[i]){
            stk.push(i);
            while(!stk.empty()){
                int current = stk.top();
                stk.pop();
                if(!required[current]){
                    required[current] = true;
                    if(matrix.projects[current].q_i !=0){
                        stk.push(matrix.projects[current].q_i);
                    }
                }
            }
        }
    }

    vector<int> in_degree(n+1, 0);
    for(int i=1;i<=n;i++){
        if(required[i] && matrix.projects[i].q_i !=0 && required[matrix.projects[i].q_i]){
            in_degree[i]++;
        }
    }

    auto cmp = [&](const int a, const int b) -> bool {
        return matrix.projects[a].b_i < matrix.projects[b].b_i;
    };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    for(int i=1;i<=n;i++){
        if(required[i] && in_degree[i]==0){
            pq.push(i);
        }
    }

    long long capital = u;
    long long total_profit =0;
    while(!pq.empty()){
        int proj = pq.top();
        pq.pop();
        long long new_capital = capital + matrix.projects[proj].b_i;
        if(new_capital >=0){
            capital = new_capital;
            total_profit += matrix.projects[proj].b_i;
            for(auto &child: matrix.projects[proj].children){
                if(required[child]){
                    in_degree[child]--;
                    if(in_degree[child]==0){
                        pq.push(child);
                    }
                }
            }
        }
    }

    io.writeOutput(total_profit);
}
