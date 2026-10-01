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
		ll sum = accumulate(v.begin(), v.end(), 0LL);

		for (int i = 0; i < n; i++) v[i] = 2 * (i + 1) - v[i];

		ll mx = 0, cur = 0;
		for (auto e : v) {
			cur += e;
			mx = max(mx, cur);
			if (cur < 0) cur = 0;
		}
		cout << sum + mx << "\n";
	}

	return 0;
}
