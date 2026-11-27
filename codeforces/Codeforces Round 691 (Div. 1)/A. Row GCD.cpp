#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<ll> a(n), b(m);
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;

	ll g = 0;
	for (int i = 1; i < n; i++) g = __gcd(g, abs(a[0] - a[i]));

	for (auto e : b) {
		cout << __gcd(g, a[0] + e) << " ";
	}

	return 0;
}
