#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	// cout << (1 << 20) * 100 << "::\n";

	int n, m;
	cin >> n >> m;

	vector<ll> v(n);
	for (auto &e : v) cin >> e;

	vector<ll> sum(1 << n);
	for (int mask = 1; mask < (1 << n); mask++) {
		int i = __builtin_ctz(mask);
		sum[mask] = sum[mask ^ (1 << i)] + v[i];
	}

	ll k = sum.back() / m;
	ll ans = 0;

	int canuse = (1 << n) - 1;
	for (int cnt = 1; cnt <= m; cnt++) {
		ll target = k * cnt;
		while (1) {
			int res = -1;
			for (int mask = canuse; mask > 0; mask = (mask - 1) & canuse) {
				if (sum[mask] == target) {
					res = mask;
					break;
				}
			}
			if (~res) {
				canuse ^= res;
				ans += cnt - 1;
			}
			else break;
		}
	}

	assert(!canuse);
	cout << ans;

	return 0;
}
