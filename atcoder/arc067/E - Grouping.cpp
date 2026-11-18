#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll MOD = 1e9 + 7;
	auto binpow = [&](ll a, ll n) {
		ll res = 1;
		for (; n; n >>= 1) {
			if (n & 1) res = res * a % MOD;
			a = a * a % MOD;
		}
		return res;
	};
	auto modInv = [&](ll a) { return binpow(a, MOD - 2); };
	constexpr int N = 1005;
	static ll fac[N + 1] = {1}, ifac[N + 1]{};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N] = modInv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

	int n, a, b, c, d;
	cin >> n >> a >> b >> c >> d;

	vector dp(b + 2, vector<ll>(n + 1));
	dp[b + 1][0] = 1;
	for (int sz = b; sz >= a; sz--) {
		for (int rem = 0; rem <= n; rem++) {
			ll x = ifac[sz];
			for (ll pw = 1, cnt = 0; cnt <= rem / sz; ++cnt, pw = pw * x % MOD) {
				if (cnt == 0 || cnt >= c && cnt <= d) {
					dp[sz][rem] += pw * ifac[cnt] % MOD * dp[sz + 1][rem - sz * cnt];
					dp[sz][rem] %= MOD;
				}
			}
		}
	}
	cout << dp[a][n] * fac[n] % MOD;

	return 0;
}
