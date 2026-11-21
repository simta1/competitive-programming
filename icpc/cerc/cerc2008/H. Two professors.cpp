#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<pair<int, int>> v(n);
		for (auto &[s, e] : v) cin >> s >> e;

		if (v[1].second <= v[0].first) swap(v[0], v[1]);

		vector<array<int, 3>> evt;
		for (int i = 0; i < n; i++) {
			auto [s, e] = v[i];
			evt.push_back({s, 1, i});
			evt.push_back({e, -1, i});
		}

		sort(evt.begin(), evt.end());
		int cur = 0, mx = 0;
		for (auto [t, add, idx] : evt) {
			cur += add;
			mx = max(mx, cur);
		}

		if ([&]() {
			if (v[0].second > v[1].first) return true;
			int e1 = v[0].second, s2 = v[1].first;
			bool flag = 0, has = 0;
			vector<bool> same(n);
			same[0] = 1;
			for (auto [t, add, idx] : evt) {
				cur += add;
				if (t == e1 && idx == 0) flag = 1;

				if (flag) {
					if (add > 0) {
						if (!has && cur == mx) {
							same[idx] = 1;
							has = 1;
						}
					}
					else {
						if (same[idx]) has = 0;
						if (!has && cur < mx - 1) break;
					}
				}
			}
			return !same[1];
		}()) cout << mx << "\n";
		else cout << mx + 1 << "\n";
	}

	return 0;
}
