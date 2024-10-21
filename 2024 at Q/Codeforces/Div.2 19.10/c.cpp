#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        
        int count_ones = 0;
        for(char c : s){
            if(c == '1') count_ones++;
        }
        
        
        if(count_ones >= 2){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}
