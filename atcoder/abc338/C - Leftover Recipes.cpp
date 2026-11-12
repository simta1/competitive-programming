#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<ll> v(n), a(n), b(n);
	for (auto &e : v) cin >> e;
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	int ans = 0;
	for (int x = 0; x <= 1e6; x++) {
		bool flag = 1;
		int y = 1e6;
		for (int i = 0; i < n; i++) {
			if (a[i] * x > v[i]) {
				flag = 0;
				break;
			}
			if (b[i]) y = min<ll>(y, (v[i] - a[i] * x) / b[i]);
		}
		if (flag) ans = max(ans, x + y);
	}
	cout << ans;

	return 0;
}
