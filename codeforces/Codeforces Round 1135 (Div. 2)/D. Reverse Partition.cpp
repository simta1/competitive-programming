#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;

main() {
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
	constexpr int N = 2e5 + 5;
	static ll fac[N + 1] = {1}, ifac[N + 1]{};
	for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[N] = modInv(fac[N]);
	for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	auto nCr = [&](int n, int r) {
		return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
	};


	int TC;
	for (cin >> TC; TC--;) {
		int n, m, q;
		cin >> n >> m >> q;

		vector<ll> v(n);
		for (auto &e : v) cin >> e;

		auto r = v;
		reverse(r.begin(), r.end());

		for (int i = 1; i < n; i++) v[i] += v[i - 1];
		for (int i = 1; i < n; i++) r[i] += r[i - 1];

		for (int i = 0; i < n; i++) v[i] -= r[i];

		vector<vector<ll>> tree(4 * n);
		auto build = [&](auto &&build, int node, int s, int e) -> void {
			if (s == e) {
				tree[node].push_back(v[s]);
				return;
			}
			int m = s + e >> 1;
			build(build, node << 1, s, m);
			build(build, node << 1 | 1, m + 1, e);
			auto &l = tree[node << 1];
			auto &r = tree[node << 1 | 1];
			merge(l.begin(), l.end(), r.begin(), r.end(), back_inserter(tree[node]));
		};
		build(build, 1, 0, n - 1);

		auto qry = [&](auto &&qry, int node, int s, int e, int l, int r, int val) -> int {
			if (l <= s && e <= r) return upper_bound(tree[node].begin(), tree[node].end(), val) - lower_bound(tree[node].begin(), tree[node].end(), val);
			if (l > e || s > r) return 0;
			int m = s + e >> 1;
			return qry(qry, node << 1, s, m, l, r, val) + qry(qry, node << 1 | 1, m + 1, e, l, r, val);
		};
		auto f = [&](int l, int r, int val) {
			if (l > r) return 0LL;
			return qry(qry, 1, 0, n - 1, l, r, val);
		};

		int zero = f(0, n - 1, 0);
		while (q--) {
			int l, add;
			cin >> l >> add;
			--l;
			int r = n - 1 - l;
			int cnt = zero;
			if (l != r) {
				if (l > r) {
					swap(l, r);
					add *= -1;
				}
				cnt = f(0, l - 1, 0) + f(l, r - 1, -add) + f(r, n - 1, 0);
			}
			if (cnt >= m) cout << nCr(cnt - 1, m - 1) << "\n";
			else cout << "0\n";
		}
	}

	return 0;
}
