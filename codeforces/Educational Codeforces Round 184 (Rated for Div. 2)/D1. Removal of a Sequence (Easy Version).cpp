#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int x;
		ll y, k;
		cin >> x >> y >> k;

		auto check = [&](ll mid) {
			for (int _ = x; _--;) mid -= mid / y;
			return mid >= k;
		};

		ll tmp = 1e12 + 1;
		ll lo = 0, hi = tmp;
		while (lo + 1 < hi) {
			ll mid = lo + hi >> 1;
			if (check(mid)) hi = mid;
			else lo = mid;
		}

		cout << (hi == tmp ? -1 : hi) << "\n";
	}

	return 0;
}
