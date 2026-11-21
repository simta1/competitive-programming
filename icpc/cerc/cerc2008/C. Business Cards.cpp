#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
	if (b == 0) return {1, 0, a};
	auto [x, y, g] = egcd(b, a % b);
	return {y, x - (a / b) * y, g};
} // x<=b/g, y<=a/g

bool f(int a, int b, int c, int d) {
	if (c % a == 0 && d % b == 0) return true;
	if (c % a == 0 && c % b == 0) {
		auto [x, y, g] = egcd(a, b);
		if (d % g == 0) {
			x *= d / g, y *= d / g;
			// ax+by=d
			if (x >= 0) {
				int q = x / (b / g);
				if (y + q * (a / g) >= 0) return true;
			}
			if (y >= 0) {
				int q = y / (a / g);
				if (x + q * (b / g) >= 0) return true;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;

		if (f(a, b, c, d) || f(a, b, d, c)) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}
