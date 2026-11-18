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
	constexpr int N = 9e5 + 5;
	static ll fac[N + 1] = {1}, ifac[N + 1]{};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N] = modInv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	auto nCr = [&](int n, int r) {
		if (r < 0 || r > n) return 0LL;
		return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
	};

	static ll pw[int(6e5 + 1)] = {1};
	for (int i = 1; i <= 6e5; i++) pw[i] = pw[i - 1] * 3 % MOD;

	int n, m, k;
	cin >> n >> m >> k;

	ll ans = 0;
	ll x = 1;
	for (int i = 0; i <= m + k; i++) {
		ans += nCr(n + i - 1, i) * pw[m + k - i] % MOD * x;
		ans %= MOD;
		x = (2 * x - nCr(i, m) - nCr(i, k)) % MOD;
	}
	if (ans < 0) ans += MOD;
	cout << ans;

	return 0;
}
