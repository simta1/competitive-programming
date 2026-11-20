#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using ld = double;
const ld PI = acos(-1);

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	while (1) {
		int n, r;
		cin >> n >> r;
		if (!n && !r) break;

		vector<pair<int, int>> v(n);
		for (auto &[x, y] : v) cin >> x >> y;

		int ans = 1;
		for (int i = 0; i < n; i++) {
			auto [x1, y1] = v[i];
			vector<pair<ld, int>> evt;
			auto add = [&](ld a, ld b) {
				evt.emplace_back(a, 0);
				evt.emplace_back(b, 1);
			};
			for (int j = 0; j < n; j++) if (i != j) {
				auto [x2, y2] = v[j];
				ll dx = x2 - x1, dy = y2 - y1;
				if (dx * dx + dy * dy > 4 * r * r) continue;

				ld theta = atan2(dy, dx);
				ld alpha = acos(hypot(dx, dy) / 2 / r);
				ld a = theta - alpha, b = theta + alpha;
				if (a < 0) a += 2 * PI;
				if (b < a) b += 2 * PI;
				add(a, b);
				add(a + 2 * PI, b + 2 * PI);
			}
			sort(evt.begin(), evt.end());

			int cur = 0;
			for (auto [_, end] : evt) {
				int add = end ? -1 : 1;
				cur += add;
				ans = max(ans, cur + 1);
			}
		}
		cout << "It is possible to cover " << ans << " points.\n";
	}

	return 0;
}
