#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> v(n + 1);
	for (int i = 1; i <= n; i++) cin >> v[i];

	constexpr ll MOD = 998'244'353;

	ll ans = 0;
	for (int bit = 0; bit < 30; bit++) {
		vector<bool> pfs(n + 1);
		for (int i = 1; i <= n; i++) pfs[i] = pfs[i - 1] ^ (v[i] >> bit & 1);

		int cnt[2]{};
		ll sum[2]{};
		ll res = 0;
		for (int i = 0; i <= n; i++) {
			ll c = cnt[!pfs[i]];
			ll s = sum[!pfs[i]];
			res += i * c - s;
			res %= MOD;
			++cnt[pfs[i]];
			sum[pfs[i]] += i;
			if (sum[pfs[i]] >= MOD) sum[pfs[i]] -= MOD;
		}
		if (res < 0) res += MOD;
		ans += res * (1 << bit);
		ans %= MOD;
	}
	cout << ans;

	return 0;
}
