#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
ll binpow(ll a, ll n) {
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

ll modInv(ll a) {
	return binpow(a, MOD - 2);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, k;
	cin >> n >> k;

	constexpr ll MOD = 998'244'353;
	vector dp(n + 1, vector<ll>(k));
	fill(dp[0].begin(), dp[0].end(), 1);
	for (int i = 1; i <= n; i++) {
		dp[i][0] = dp[i - 1][k - 1] - dp[i - 1][k - 2];
		dp[i][0] %= MOD;
		for (int j = 1; j < k; j++) {
			int pj = j - 1;
			ll x = dp[i - 1][pj] - (pj ? dp[i - 1][pj - 1] : 0);
			dp[i][j] = x * (k - pj);
			dp[i][j] += dp[i - 1].back() - dp[i - 1][j - 1];
			dp[i][j] %= MOD;
		}

		for (int j = 1; j < k; j++) {
			dp[i][j] += dp[i][j - 1];
			dp[i][j] %= MOD;
		}
	}

	vector<ll> pw(n + 1, 1);
	for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * k % MOD;

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dp[i][0] * pw[n - i];
		ans %= MOD;
	}
	if (ans < 0) ans += MOD;
	cout << ans;

	return 0;
}
