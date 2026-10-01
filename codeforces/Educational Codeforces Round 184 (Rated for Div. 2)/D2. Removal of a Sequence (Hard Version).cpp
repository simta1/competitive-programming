#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr ll INF = 1e12;

	int TC;
	for (cin >> TC; TC--;) {
		ll x, y, k;
		cin >> x >> y >> k;

		cout << [&]() -> ll {
			if (y == 1) return -1;

			while (x) {
				ll add = (k - 1) / (y - 1);
				if (!add) break;

				ll nk = (add + 1) * (y - 1) + 1;
				ll cnt = min(x, (nk - k + add - 1) / add);
				x -= cnt;
				k += cnt * add;
				if (k > INF) return -1; 
			}
			return k;
		}() << "\n";
	}

	return 0;
}
