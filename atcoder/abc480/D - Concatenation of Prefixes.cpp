#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector<ll> pfs(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> pfs[i];
		pfs[i] += pfs[i - 1];
	}
	auto ppfs = pfs;
	for (int i = 1; i <= n; i++) ppfs[i] += ppfs[i - 1];

	vector<ll> pos(n + 1);
	for (int i = 1; i <= n; i++) pos[i] = pos[i - 1] + i;

	auto f = [&](ll i) {
		int idx = lower_bound(pos.begin(), pos.end(), i) - pos.begin();
		return pair{idx, i - pos[idx - 1]};
	};
	
	while (q--) {
		ll l, r;
		cin >> l >> r;
		auto [g1, i1] = f(l);
		auto [g2, i2] = f(r);
		// cout << g1 << " " << i1 << " " << g2 << " " << i2 << "::\n";
		if (g1 == g2) cout << pfs[i2] - pfs[i1 - 1] << "\n";
		else {
			ll ans = pfs[g1] - pfs[i1 - 1];
			// cout << q << " " << ans << "\n";
			ans += pfs[i2];
			// cout << q << " " << ans << "\n";
			if (g1 + 1 < g2) ans += ppfs[g2 - 1] - ppfs[g1];
			// cout << q << " " << ans << "\n";
			cout << ans << "\n";
		}
	}

	return 0;
}
