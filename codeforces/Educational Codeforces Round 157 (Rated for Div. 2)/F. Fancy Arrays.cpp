#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
ll binpow(ll a, int n) {
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

using mat = array<array<ll, 40>, 40>;
mat op(mat a, mat b) {
	mat res{};
	for (int i = 0; i < 40; i++) {
		for (int k = 0; k < 40; k++) {
			for (int j = 0; j < 40; j++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
			}
		}
	}
	return res;
}

mat binpow(mat a, int n) {
	mat res{};
	for (int i = 0; i < 40; i++) res[i][i] = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = op(res, a);
		a = op(a, a);
	}
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, x, k;
		cin >> n >> x >> k;

		ll ans = binpow(2 * k + 1, n - 1) * (x + k) % MOD;

		mat a{};
		for (int i = 0; i < x; i++) {
			for (int j = max(0, i - k); j <= min(x - 1, i + k); j++) {
				a[i][j] = 1;
			}
		}
		a = binpow(a, n - 1);
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				ans -= a[i][j];
			}
		}
		ans %= MOD;
		if (ans < 0) ans += MOD;
		cout << ans << "\n";
	}

	return 0;
}
