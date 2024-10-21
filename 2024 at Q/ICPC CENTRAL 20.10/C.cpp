#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1'000'000'007;


ll clcm(ll a, ll b) {
    if(a == 0 || b == 0) return 0;
    ll g = gcd(a, b);
    return (a / g) * b;
}


vector<pair<ll, ll>> updateDP(const vector<pair<ll, ll>>& dp, const vector<pair<ll, ll>>& tmp) {
    vector<pair<ll, ll>> new_dp;
    int p1 = 0, p2 = 0;
    int sizeDP = dp.size();
    int sizeTmp = tmp.size();
    
    while(p1 < sizeDP && p2 < sizeTmp){
        if(dp[p1].first < tmp[p2].first){
            new_dp.emplace_back(dp[p1].first, dp[p1].second);
            p1++;
        }
        else if(dp[p1].first > tmp[p2].first){
            new_dp.emplace_back(tmp[p2].first, tmp[p2].second);
            p2++;
        }
        else{
            ll combined = (dp[p1].second + tmp[p2].second) % MOD;
            new_dp.emplace_back(dp[p1].first, combined);
            p1++;
            p2++;
        }
    }
    while(p1 < sizeDP){
        new_dp.emplace_back(dp[p1].first, dp[p1].second);
        p1++;
    }
    while(p2 < sizeTmp){
        new_dp.emplace_back(tmp[p2].first, tmp[p2].second);
        p2++;
    }
    return new_dp;
}


ll cT(const vector<pair<ll, ll>>& dp) {
    ll total = 0;
    for(auto &[lcm_val, cnt] : dp){
        total = (total + (lcm_val % MOD) * (cnt % MOD)) % MOD;
    }
    return total;
}


void pTC(int N, const vector<int>& A) {
    vector<pair<ll, ll>> dp;
    for(int i = 0; i < N; i++){
        ll ai = A[i];
        vector<pair<ll, ll>> tmp;
        for(auto &[lcm_val, cnt] : dp){
            ll newLcm = clcm(lcm_val, ai);
            tmp.emplace_back(newLcm, cnt);
        }
        tmp.emplace_back((ll)ai, 1);
        sort(tmp.begin(), tmp.end());
        dp = updateDP(dp, tmp);
    }
    ll total = cT(dp);
    cout << total << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        vector<int> A(N);
        for(int i = 0; i < N; i++) cin >> A[i];
        pTC(N, A);
    }
}
