#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll n, ll b) {
	ll res = 0; 
	while (n) {
		res += n % b;
		n /= b;
	}
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	ll n, s;
	cin >> n >> s;

	if (n < s) {
		cout << -1;
		return 0;
	}
	else if (n == s) {
		cout << n + 1;
		return 0;
	}

	int b = 2;
	for (; b <= n / b; b++) {
		if (f(n, b) == s) {
			cout << b;
			return 0;
		}
	}

	constexpr ll INF = 1e18;
	ll ans = INF;
	for (int x = 1; x <= (n - s) / x; x++) if ((n - s) % x == 0) {
		ll x2 = (n - s) / x;
		for (ll b : vector{x + 1, x2 + 1}) {
			if (f(n, b) == s) ans = min(ans, b);
		}
	}
	if (ans == INF) cout << -1;
	else cout << ans;

	return 0;
}
