#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct TestCase {
    int N;          
    int X;         
    vector<int> A;  
};

struct Matrix {
    int T;                       
    vector<TestCase> test_cases; 
};

struct IOManager {
    
    void read_input(Matrix &matrix){
        cin >> matrix.T;
        for(int i=0;i<matrix.T;i++){
            TestCase tc;
            cin >> tc.N >> tc.X;
            tc.A.resize(tc.N);
            for(int j=0;j<tc.N;j++) cin >> tc.A[j];
            matrix.test_cases.push_back(tc);
        }
    }
    
    
    void write_output(vector<string> &results){
        for(auto &res: results){
            cout << res << "\n";
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("gcandy.inp", "r", stdin);
    freopen("gcandy.out", "w", stdout);
    
    
    Matrix matrix;
    IOManager io;
    
   
    io.read_input(matrix);
    
    
    vector<string> results;
    
    
    for(int i=0;i<matrix.T;i++){
        TestCase &tc = matrix.test_cases[i];
        int N = tc.N;
        int X = tc.X;
        vector<int> &A = tc.A;
        
        
        ll total = 0;
        int max_a = 0;
        for(int j=0; j<N; j++){
            total += A[j];
            if(A[j] > max_a) max_a = A[j];
        }
        
        
        if(max_a <= X && total <= 2LL * X){
            results.push_back("YES");
        }
        else{
            results.push_back("NO");
        }
    }
    
    
    io.write_output(results);
    
    return 0;
}