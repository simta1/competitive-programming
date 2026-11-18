#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll MOD = 1e9 + 7;
	constexpr int N = 405;
	static ll pw[N + 1][N + 1];
	for (int j = 1; j <= N; j++) pw[0][j] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			pw[i][j] = pw[i - 1][j] * j % MOD;
		}
	}
	for (int i = 0; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			pw[i][j] += pw[i][j - 1];
			if (pw[i][j] >= MOD) pw[i][j] -= MOD;
		}
	}
	auto f = [&](int a, int b, int exp) {
		auto &pfs = pw[exp];
		return pfs[b] - pfs[a - 1];
	};

	int n, c;
	cin >> n >> c;

	vector<int> a(n), b(n);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	vector dp(n, vector<ll>(c + 1));
	for (int j = 0; j <= c; j++) dp[0][j] = f(a[0], b[0], j);

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= c; j++) {
			for (int k = 0; k <= j; k++) {
				dp[i][j] += dp[i - 1][k] % MOD * f(a[i], b[i], j - k);
				dp[i][j] %= MOD;
			}
		}
	}
	ll ans = dp[n - 1][c];
	if (ans < 0) ans += MOD;
	cout << ans;

	return 0;
}
