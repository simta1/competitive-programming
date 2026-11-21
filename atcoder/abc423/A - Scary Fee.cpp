#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	ll x, c;
	cin >> x >> c;

	auto check = [&](ll mid) {
		return mid + mid / 1000 * c <= x;
	};

	ll lo = 0, hi = 1e9;
	while (lo + 1 < hi) {
		ll mid = lo + hi >> 1;
		if (check(mid * 1000)) lo = mid;
		else hi = mid;
	}
	cout << lo * 1000;

	return 0;
}
