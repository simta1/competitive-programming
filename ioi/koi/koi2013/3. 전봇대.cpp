#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;

	auto f = [&](ll d) {
		ll res = 0;
		for (int i = 0; i < n; i++) {
			res += abs(v[i] - i * d);
		}
		return res;
	};

	ll lo = 0, hi = 1e9;
	while (lo + 2 < hi) {
		ll p = (2 * lo + hi) / 3;
		ll q = (lo + 2 * hi) / 3;
		if (f(p) > f(q)) lo = p;
		else hi = q;
	}

	ll ans = 1e18;
	for (int i = lo; i <= hi; i++) ans = min(ans, f(i));
	cout << ans;

	return 0;
}
