#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
    int width;
    int height;
};

struct TestCase {
    int n;
    vector<Rectangle> rectangles;

    void read() {
        cin >> n;
        rectangles.resize(n);
        for(int i = 0; i < n; ++i) {
            cin >> rectangles[i].width >> rectangles[i].height;
        }
    }

    long long compute_min_perimeter() const {
        int max_width = 0;
        int max_height = 0;
        for(const auto &rect : rectangles) {
            if(rect.width > max_width) max_width = rect.width;
            if(rect.height > max_height) max_height = rect.height;
        }
        return 2LL * (max_width + max_height);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        TestCase tc;
        tc.read();
        cout << tc.compute_min_perimeter() << "\n";
    }
}
