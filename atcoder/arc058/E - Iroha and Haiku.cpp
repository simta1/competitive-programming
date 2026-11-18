#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll MOD = 1e9 + 7;
void add(ll &a, ll b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr int N = 40;
	static ll pw[N + 1] = {1};
	for (int i = 1; i <= N; i++) pw[i] = pw[i - 1] * 10 % MOD;

	int n, x, y, z;
	cin >> n >> x >> y >> z;
	y += z;
	x += y;
	--x, --y, --z;

	constexpr int M = 1 << 17;
	array<ll, M> dp{};
	dp[0] = 1;

	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		array<ll, M> ndp{};
		for (int mask = 0; mask < M; mask++) {
			if (!dp[mask]) continue;
			for (int d = 1; d <= 10; d++) {
				int nmask = (mask << d) & (M - 1) | (1 << d - 1);
				add(ndp[nmask], dp[mask]);
			}
		}
		swap(ndp, dp);
		for (int mask = 0; mask < M; mask++) {
			bool a = mask >> x & 1;
			bool b = mask >> y & 1;
			bool c = mask >> z & 1;
			if (a && b && c) {
				ans += dp[mask] * pw[n - i];
				ans %= MOD;
				dp[mask] = 0;
			}
		}
	}
	cout << ans;

	return 0;
}
