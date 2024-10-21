#include <bits/stdc++.h>
using namespace std;

int n;

int main() {
    freopen("test.inp", "r", stdin);   // Mở file test.inp cho đầu vào
    freopen("test.out", "w", stdout);  // Mở file test.out cho đầu ra
    
    cin >> n;
    set<pair<int, int> > st;  // Thêm dấu cách giữa hai dấu ngoặc >>
    
    for (int i = 0; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        st.insert(make_pair(x, y));  // Sử dụng make_pair thay vì {x, y}
    }
    
    cout << st.size();
}
