#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct TestCase {
    int N;
    int K;
    vector<int> A;
};

struct MatrixDP {
    int N;
    int K;
    vector<vector<ll> > dp;
    
    MatrixDP(int n, int k) : N(n), K(k), dp(n+1, vector<ll>(k+1, INF)) {}
};

struct IOManager {
    void read_input(TestCase &tc){
        cin >> tc.N >> tc.K;
        tc.A.resize(tc.N);
        for(int i=0; i<tc.N; i++) cin >> tc.A[i];
    }
    
    void write_output(long long result){
        cout << result;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("snakes.inp", "r", stdin);
    freopen("snakes.out", "w", stdout);
    TestCase tc;
    IOManager io;
    
    io.read_input(tc);
    
    int N = tc.N;
    int K = tc.K;
    vector<int> A = tc.A;
    
    vector<vector<ll> > sum(N+1, vector<ll>(N+1, 0));
    vector<vector<int> > maxi(N+1, vector<int>(N+1, 0));
    
    for(int i=1; i<=N; i++){
        sum[i][i] = A[i-1];
        maxi[i][i] = A[i-1];
        for(int j=i+1; j<=N; j++){
            sum[i][j] = sum[i][j-1] + A[j-1];
            maxi[i][j] = max(maxi[i][j-1], A[j-1]);
        }
    }
    
    MatrixDP matrix(N, K);
    matrix.dp[0][0] = 0;
    
    for(int i=1; i<=N; i++){
        for(int k=0; k<=K; k++){
            for(int j=0; j<i; j++){
                if(k - (j > 0 ? 1 : 0) < 0) continue;
                if(k - (j > 0 ? 1 : 0) > K) continue;
            }
        }
    }
    
    MatrixDP dp_matrix(N, K);
    dp_matrix.dp[0][0] = 0;
    for(int i=1; i<=N; i++){
        for(int k=0; k<=K; k++){
            for(int j=0; j<i; j++){
                if(k == 0 && j > 0) continue;
                if(j == 0 && k > K) continue;
                int new_k = k - (j > 0 ? 1 : 0);
                if(new_k < 0) continue;
                dp_matrix.dp[i][k] = min(dp_matrix.dp[i][k], dp_matrix.dp[j][new_k] + (ll)maxi[j+1][i] * (i - j) - sum[j+1][i]);
            }
        }
    }
    
    ll result = INF;
    for(int k=0; k<=K; k++) {
        result = min(result, dp_matrix.dp[N][k]);
    }
    
    io.write_output(result);
    
    return 0;
}
