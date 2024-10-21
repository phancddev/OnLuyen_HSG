#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_BITS = 20;
const int MASK_SIZE = 1 << MAX_BITS;

struct InputData {
    int N;
    ll k;
    vector<int> A;
};

struct BitMasks {
    vector<bitset<5000>> masks;
    BitMasks(int size) : masks(size, bitset<5000>()) {}
};

InputData readInput() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    InputData data;
    cin >> data.N >> data.k;
    data.A.resize(data.N);
    for(auto &x : data.A) cin >> x;
    return data;
}

BitMasks preBit(const vector<int> &A, int N) {
    BitMasks BitM(MAX_BITS);
    for(int q = 0; q < N; q++) {
        for(int b = 0; b < MAX_BITS; b++) {
            if( (A[q] >> b) & 1 ) {
                BitM.masks[b].set(q);
            }
        }
    }
    return BitM;
}

vector<ll> computeFPrime(const vector<ll> &C) {
    vector<ll> F_prime = C;
    for(int b = 0; b < MAX_BITS; b++) {
        for(int mask = 0; mask < MASK_SIZE; mask++) {
            if(mask & (1 << b)) {
                F_prime[mask] += F_prime[mask ^ (1 << b)];
            }
        }
    }
    return F_prime;
}

ll calAll(int x, const vector<int> &A, int N, const vector<ll> &F_prime) {
    int x_complement = (~x) & (MASK_SIZE -1);
    return F_prime[x_complement];
}

pair<int, int> FPQ(int x, ll k, const vector<int> &A, int N, const vector<ll> &F_prime) {
    for(int p = 0; p < N; p++) {
        int y_p = A[p] & x;
        ll cnt_p;
        if(y_p < MASK_SIZE) {
            cnt_p = calAll(y_p, A, N, F_prime);
        }
        else {
            cnt_p = 0;
        }
        if(k > cnt_p){
            k -= cnt_p;
        }
        else{
            for(int q = 0; q < N; q++) {
                if( (A[q] & y_p) == 0 ){
                    k -=1;
                    if(k ==0){
                        return {p +1, q +1};
                    }
                }
            }
        }
    }
    return {-1, -1};
}

int main(){
    InputData data = readInput();
    int N = data.N;
    ll k = data.k;
    vector<int> A = data.A;
    
    vector<ll> C(MASK_SIZE, 0);
    for(int p = 0; p < N; p++) {
        int a_p = A[p];
        for(int q = 0; q < N; q++) {
            int y = a_p & A[q];
            C[y]++;
        }
    }
    
    vector<ll> F_prime = computeFPrime(C);
    
    bool found = false;
    for(int i = 0; i < N && !found; i++) {
        for(int j = 0; j < N && !found; j++) {
            int x = A[i] & A[j];
            ll cnt = calAll(x, A, N, F_prime);
            if(k > cnt){
                k -= cnt;
            }
            else{
                pair<int, int> pq = FPQ(x, k, A, N, F_prime);
                if(pq.first != -1 && pq.second != -1){
                    cout << (i +1) << " " << (j +1) << " " << pq.first << " " << pq.second << "\n";
                    return 0;
                }
                else{
                    cout << "-1\n";
                    return 0;
                }
            }
        }
    }
    cout << "-1\n";
    return 0;
}
