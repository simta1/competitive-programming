#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		int mx = *max_element(v.begin(), v.end());
		int mn = *min_element(v.begin(), v.end());
		int ans = 0;
		while (mx > mn) {
			++ans;
			mx = mx + mn >> 1;
		}
		cout << ans << "\n";
		if (ans <= n && ans) {
			for (int i = 0; i < ans; i++) cout << mn << " ";
			cout << "\n";
		}
	}

	return 0;
}
