#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    long long k;
    long long period;
    vector<long long> positions;
    Matrix(){}
};

struct IOManager {
    void readTestCase(long long &n, long long &k){
        cin >> n >> k;
    }
    void writeResult(long long res){
        cout << res << '\n';
    }
};
//sweetie.zz
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    const long long MOD = 1000000007;
    IOManager io;
    int t;
    cin >> t;
    vector<pair<long long, long long>> testCases(t);
    for(auto &tc : testCases){
        io.readTestCase(tc.first, tc.second);
    }
    const int MAX_K = 100000;
    vector<Matrix> cache(MAX_K +1, Matrix());
    vector<bool> processed(MAX_K +1, false);
    for(auto &[n,k] : testCases){
        if(!processed[k]){
            Matrix m;
            m.k =k;
            if(k==1){
                m.period=1;
                m.positions.push_back(1);
            }
            else{
                long long f0=0, f1=1, fi;
                long long i=1;
                while(true){
                    fi=(f0 +f1) %k;
                    if(fi==0){
                        m.positions.push_back(i+1);
                    }
                    if(f0==0 && f1==1 && i >1){
                        m.period=i-1;
                        break;
                    }
                    f0=f1;
                    f1=fi;
                    i++;
                }
            }
            cache[k]=m;
            processed[k]=true;
        }
        Matrix m = cache[k];
        long long m_count = m.positions.size();
        long long q = n / m_count;
        long long r =n % m_count;
        long long G;
        if(r==0){
            G = (((q-1) % MOD) * (m.period % MOD)) % MOD;
            G = (G + m.positions[m_count -1]) % MOD;
        }
        else{
            G = ((q % MOD) * (m.period % MOD)) % MOD;
            G = (G + m.positions[r-1]) % MOD;
        }
        io.writeResult(G);
    }
}