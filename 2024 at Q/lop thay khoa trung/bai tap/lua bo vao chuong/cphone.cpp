// #include <iostream>
// #include <freopen>
#include <bits/stdc++.h>
using namespace std;

#define MAX_BD 1000 

int kg[1000001];  
int fn[MAX_BD + 1];  

int main() {
    freopen("cphone.inp", "r", stdin);
    freopen("cphone.out", "w", stdout);
    int nkg;
    cin >> nkg;

    for(int i = 1; i <= MAX_BD; i++) {
        fn[i] = 0;
    }

    
    for(int i = 1; i <= nkg; i++) {
        cin >> kg[i];
        fn[kg[i]] += 1;
    }

    
    int max_votes = 0;
    for(int i = 1; i <= MAX_BD; i++) {
        if(fn[i] > max_votes) {
            max_votes = fn[i];
        }
    }

    
    for(int i = 1; i <= MAX_BD; i++) {
        if(fn[i] == max_votes) {
            cout << i << '\n';
        }
    }

    return 0;
}