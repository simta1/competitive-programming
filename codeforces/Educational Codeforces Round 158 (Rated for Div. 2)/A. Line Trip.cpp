#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, x;
		cin >> n >> x;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		int ans = 0;
		for (int i = 1; i < n; i++) ans = max(ans, v[i] - v[i - 1]);
		ans = max(ans, v[0]);
		ans = max(ans, 2 * (x - v.back()));
		cout << ans << "\n";
	}

	return 0;
}
