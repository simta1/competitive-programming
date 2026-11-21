#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using hh = __int128_t;
using mat = array<array<hh, 3>, 3>;
mat op(mat &a, mat &b, hh mod) {
	mat res{};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
			res[i][j] %= mod;
		}
	}
	return res;
}

mat binpow(mat a, ll n, hh mod) {
	mat res{};
	res[0][0] = res[1][1] = res[2][2] = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = op(res, a, mod);
		a = op(a, a, mod);
	}
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		ll k, n, mod;
		cin >> k >> n >> mod;

		if (k == 1) {
			cout << n % mod << "\n";
			continue;
		}

		mod *= 4;

		hh x = (4 * k * k - 2) % mod;
		if (x < 0) x += mod;
		mat a = {{
			{x, mod - 1, 0},
			{1, 0, 0},
			{1, 0, 1}
		}};
		hh S = 2;
		if (n > 1) {
			auto powed = binpow(a, n - 1, mod);
			S = (powed[2][0] * x + powed[2][1] * 2 + powed[2][2] * 2) % mod;
		}

		ll ans = (S + 2 * n) % mod;
		assert(ans % 4 == 0);
		cout << ans / 4 << "\n";
	}

	return 0;
}
