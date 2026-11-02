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

	ll n, m, k;
	cin >> n >> m >> k;

	ll g = __gcd(n, m);

	vector<int> a(n), b(m);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	ll n2 = n / g, m2 = m / g;
	ll lcm = n * m2;
	ll inv = modInv(n2, m2);
	auto crt = [&](int r, int s) {
		ll x = (s - r) % m;
		if (x < 0) x += m;
		if (x % g) return -1LL;
		ll x2 = x / g;
		return (x2 * inv % m2 * n + r) % lcm;
	};

	int MX = *max_element(a.begin(), a.end());
	vector<vector<int>> pos(MX + 1);
	for (int i = 0; i < m; i++) {
		if (b[i] > MX) continue;
		pos[b[i]].push_back(i);
	}

	vector<ll> same;
	for (int r = 0; r < n; r++) {
		for (auto s : pos[a[r]]) {
			ll x = crt(r, s);
			if (~x) same.push_back(x);
		}
	}

	// cout << lcm << "::\n";
	// for (auto &e : same) cout << e << " ";
	// cout << "\n";

	sort(same.begin(), same.end());
	
	ll diff = lcm - same.size();

	auto check = [&](ll x) {
		if (x / lcm > (k - 1) / diff) return true;
		ll cnt = x / lcm * diff;
		x %= lcm;
		// cout << cnt << "\n";
		cnt += x - (lower_bound(same.begin(), same.end(), x) - same.begin());
		return cnt >= k;
	};

	// cout << count(1) << "::\n";
	// count(1);

	ll lo = 0, hi = 4e18;
	while (lo + 1 < hi) {
		ll mid = lo + hi >> 1;
		if (check(mid)) hi = mid;
		else lo = mid;
	}
	cout << hi;

	return 0;
}
