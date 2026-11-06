#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using ld = double;
using P = pair<ld, ld>;
using C = array<ll, 3>;
array<P, 2> f(C &a, C &b) {
	auto [x1, y1, r1] = a;
	auto [x2, y2, r2] = b;
	ld theta = atan2(y2 - y1, x2 - x1);
	ll dx = x2 - x1;
	ll dy = y2 - y1;
	ll dsq = dx * dx + dy * dy;
	ld alpha = acos(ld(r1 * r1 + dsq - r2 * r2) / 2 / r1 / sqrt(dsq));
	return {
		pair{x1 + cos(theta + alpha) * r1, y1 + sin(theta + alpha) * r1},
		pair{x1 + cos(theta - alpha) * r1, y1 + sin(theta - alpha) * r1},
	};
}

bool in(P p, C c) {
	ld dx = p.first - c[0];
	ld dy = p.second - c[1];
	return dx * dx + dy * dy < c[2] * c[2];
}


bool meet(C &a, C &b) {
	auto [x1, y1, r1] = a;
	auto [x2, y2, r2] = b;
	ll dx = x2 - x1;
	ll dy = y2 - y1;
	return dx * dx + dy * dy < (r1 + r2) * (r1 + r2);
};
bool in(C &a, C &b) {
	auto [x1, y1, r1] = a;
	auto [x2, y2, r2] = b;
	ll dx = x2 - x1;
	ll dy = y2 - y1;
	return r1 <= r2 && dx * dx + dy * dy <= (r1 - r2) * (r1 - r2);
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<array<ll, 3>> v(n);
		for (auto &[x, y, r] : v) cin >> x >> y >> r;

		vector<bool> ans(n);
		if (n == 1 || [&]() {
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (!meet(v[i], v[j])) ans[i] = ans[j] = 1;
					else if (in(v[i], v[j])) ans[i] = 1;
					else if (in(v[j], v[i])) ans[j] = 1;
					else continue;
					return false;
				}
			}

			bool visited[16]{};
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					for (auto p : f(v[i], v[j])) {
						int mask = 0;
						for (int k = 0; k < min(4, n); k++) if (k != i && k != j) {
							if (in(p, v[k])) mask |= 1 << k;
						}
						visited[mask] = 1;
						if (i < 4) visited[mask | 1 << i] = 1;
						if (j < 4) visited[mask | 1 << j] = 1;
						if (i < 4 && j < 4) visited[mask | 1 << i | 1 << j] = 1;
					}
				}
			}

			for (int mask = 1; mask < (1 << min(4, n)); mask++) {
				if (!visited[mask]) {
					for (; mask; mask &= mask - 1) ans[__builtin_ctz(mask)] = 1;
					return false;
				}
			}
			return true;
		}()) cout << "YES\n";
		else {
			cout << "NO\n";
			for (int i = 0; i < n; i++) cout << ans[i] << " ";
			cout << "\n";
		}
	}

	return 0;
}
