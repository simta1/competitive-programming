#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
ll binpow(ll a, ll n) {
	ll res = 1;
	for (; n; n >>= 1) {
		if (n & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		ll ans = 1;

		sort(v.rbegin(), v.rend());
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && v[i] == v[j]) ++j;
			if (j - i >= 2) break;
			ans += binpow(v[i] - 1, i + 1);
		}
		cout << (ans % MOD) << "\n";
		
	}

	return 0;
}
