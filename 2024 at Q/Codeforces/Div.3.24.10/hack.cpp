#include <bits/stdc++.h>

using namespace std;

void solve() {
	unordered_map<int, int> mp; mp[0] = -1;
	int n, prefix = 0, r = -1, ans = 0;
	cin >> n;
	int a[n + 1];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++) {
		prefix += a[i];
		if(mp.find(prefix) != mp.end()) {
			int tmp = mp[prefix];
			if(tmp >= r) {
				ans++;
				r = i;
			}
		}
		mp[prefix] = i;
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
}