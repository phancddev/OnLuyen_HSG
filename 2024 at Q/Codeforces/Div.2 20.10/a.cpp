
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct TestCase {
    ll a;
    ll b;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    
   
    vector<vector<ll>> matrix(t, vector<ll>(2));
    
    
    for(int i = 0; i < t; ++i){
        cin >> matrix[i][0] >> matrix[i][1]; 
    }
    
   
    for(int i = 0; i < t; ++i){
        ll a = matrix[i][0];
        ll b = matrix[i][1];
        ll result = 0;
        
        if(a >= b){
            
            result = a;
        }
        else{
            
            if(2 * a >= b){
               
                result = 2 * a - b;
            }
            else{
                
                result = 0;
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}