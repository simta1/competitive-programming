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
	constexpr int N = 2e5;
	static ll fac[N + 1] = {1}, ifac[N + 1]{};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N] = modInv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	auto nCr = [&](int n, int r) {
		return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
	};

	int n, m, a, b;
	cin >> n >> m >> a >> b;

	ll ans = 0;
	a = n - a, ++b;
	while (a && b <= m) {
		ans += nCr(a - 1 + b - 1, b - 1) * nCr(n - a + m - b, m - b);
		ans %= MOD;
		--a, ++b;
	}
	cout << ans;

	return 0;
}
