#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main() {
    int t; // số lượng test case
    cin >> t;
    while (t--) {
        int n; // độ dài của hàng sinh viên
        cin >> n;
        vector<int> a(n); // chủ đề yêu thích của sinh viên
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        vector<vector<int>> dp(n, vector<int>(2, INF)); // dp[i][0/1] lưu số disturbance tối thiểu
        dp[0][0] = 0; // Không có disturbance tại phần tử đầu tiên nếu không swap
        dp[0][1] = 0; // Không có disturbance tại phần tử đầu tiên nếu swap với chính nó (không đổi)

        for (int i = 1; i < n; ++i) {
            // Trường hợp không swap a[i]
            dp[i][0] = dp[i-1][0] + (a[i] == a[i-1] ? 1 : 0);
            dp[i][0] = min(dp[i][0], dp[i-1][1] + (a[i] == a[n-i-1] ? 1 : 0));

            // Trường hợp swap a[i] với a[n-i-1]
            dp[i][1] = dp[i-1][0] + (a[n-i-1] == a[i-1] ? 1 : 0);
            dp[i][1] = min(dp[i][1], dp[i-1][1] + (a[n-i-1] == a[n-i-2] ? 1 : 0));
        }

        // Kết quả là lượng disturbance nhỏ nhất ở cuối mảng
        int result = min(dp[n-1][0], dp[n-1][1]);
        cout << result << endl;
    }

    return 0;
}