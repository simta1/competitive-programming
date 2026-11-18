#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;

ll binpow(ll a, ll n) {
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	ll n, k;
	cin >> n >> k;

	vector<int> ds;
	for (int i = 1; i <= n / i; i++) if (n % i == 0) {
		ds.push_back(i);
		if (i != n / i) ds.push_back(n / i);
	}

	sort(ds.begin(), ds.end());
	vector<ll> dp(ds.size());
	ll ans = 0;
	for (int i = 0; i < ds.size(); i++) {
		int d = ds[i];
		dp[i] = binpow(k, d + 1 >> 1);
		for (int j = 0; j < i; j++) {
			if (d % ds[j] == 0) dp[i] -= dp[j];
		}
		ans += dp[i] * d / (d % 2 == 0 ? 2 : 1);
		ans %= MOD;
	}
	if (ans < 0) ans += MOD;
	cout << ans;

	return 0;
}
