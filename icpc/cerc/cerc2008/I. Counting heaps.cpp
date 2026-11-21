#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
	if (b == 0) return {1, 0, a};
	auto [x, y, g] = egcd(b, a % b);
	return {y, x - (a / b) * y, g};
} // x<=b/g, y<=a/g
ll modInv(ll a, ll b) {
	auto [x, y, g] = egcd(a, b);
	return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, mod;
		cin >> n >> mod;

		vector<int> ps;
		int m = mod;
		for (int i = 2; i <= m / i; i++) if (m % i == 0) {
			int p = i;
			while (m % p == 0) m /= p;
			ps.push_back(p);
		}
		if (m > 1) ps.push_back(m);

		vector<vector<int>> adj(n + 1);
		for (int i = 2; i <= n; i++) {
			int par;
			cin >> par;
			adj[par].push_back(i);
		}

		vector<int> sz(n + 1, 1);
		auto mkt = [&](auto &&mkt, int cur, int par) -> void {
			for (auto nxt : adj[cur]) if (nxt != par) {
				mkt(mkt, nxt, cur);
				sz[cur] += sz[nxt];
			}
		};
		mkt(mkt, 1, -1);

		ll ans = 1, inv = 1;
		vector<int> cnt(ps.size());
		auto mul = [&](int x) {
			for (int i = 0; i < ps.size(); i++) {
				int p = ps[i];
				while (x % p == 0) {
					x /= p;
					++cnt[i];
				}
			}
			ans = ans * x % mod;
		};
		auto div = [&](int x) {
			for (int i = 0; i < ps.size(); i++) {
				int p = ps[i];
				while (x % p == 0) {
					x /= p;
					--cnt[i];
				}
			}
			inv = inv * x % mod;
		};
		for (int i = 1; i <= n; i++) {
			mul(i);
			div(sz[i]);
		}
		ans = ans * modInv(inv, mod) % mod;
		for (int i = 0; i < ps.size(); i++) {
			for (int e = cnt[i]; e--;) ans = ans * ps[i] % mod;
		}
		cout << ans << "\n";
	}

	return 0;
}
