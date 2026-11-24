#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<int> v(n);
		for (auto &e : v) cin >> e;
		sort(v.rbegin(), v.rend());

		vector<int> c(m);
		for (auto &e : c) cin >> e;

		int i = 0;
		while (i + 1 < n && v[i + 1] >= i + 2) ++i;
		// cout << i << "::\n";
		ll ans = 0;
		for (int j = 0; j <= i; j++) {
			ans += c[j];
		}
		for (int j = i + 1; j < n; j++) {
			ans += c[v[j] - 1];
		}
		cout << ans << "\n";
	}

	return 0;
}
