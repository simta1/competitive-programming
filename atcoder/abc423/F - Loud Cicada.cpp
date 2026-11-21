#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr int N = 20;
	static ll comb[N + 1][N + 1] = {1};
	for (int i = 1; i <= N; i++) {
		comb[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
		}
	}
	// cout << comb[20][10] << "::\n"; // 184756

	int n, m;
	ll y;
	cin >> n >> m >> y;

	vector<ll> v(n);
	for (auto &e : v) cin >> e;

	ll MX = 1'000'000'000'000'000'000;
	auto getLCM = [&](ll a, ll b) {
		if (a > MX || b > MX) return MX + 1;
		ll g = __gcd(a, b);
		a /= g;
		if (a <= MX / b) return a * b;
		return MX + 1;
	};

	ll ans = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		ll lcm = 1;
		for (int i = 0; i < n; i++) if (mask >> i & 1) lcm = getLCM(lcm, v[i]);

		int pc = __builtin_popcount(mask);
		if (pc >= m) {
			ans += comb[pc][m] * (pc - m & 1 ? -1 : 1) * (y / lcm);
		}
	}
	cout << ans;

	return 0;
}
