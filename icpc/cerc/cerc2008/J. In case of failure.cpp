#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll isqrt(ll x) {
	ll res = sqrt(x);
	while ((res + 1) <= x / (res + 1)) ++res;
	while (res && res > x / res) --res;
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<pair<ll, ll>> v(n);
		for (auto &[x, y] : v) cin >> x >> y;

		vector<pair<ll, int>> xs(n);
		for (int i = 0; i < n; i++) xs[i] = {v[i].first, i};
		sort(xs.begin(), xs.end());

		vector<ll> ans(n, LLONG_MAX);

		auto upd = [&](int l_i1, int l_i2, int r_i1, int r_i2, ll xm) {
			vector<array<ll, 3>> evt;
			for (int i = l_i1; i <= l_i2; i++) {
				int idx = xs[i].second;
				auto [x, y] = v[idx];
				ll dist2 = ans[idx];
				ll dx = x - xm;
				if (dist2 < dx * dx) continue;
				ll dy = isqrt(dist2 - dx * dx);
				evt.push_back({y - dy, 1, idx});
				evt.push_back({y + dy + 1, -1, idx});
			}
			for (int i = r_i1; i <= r_i2; i++) {
				int idx = xs[i].second;
				auto [x, y] = v[idx];
				evt.push_back({y, 2, idx});
			}

			sort(evt.begin(), evt.end());
			vector<int> ls;
			for (auto [y, op, idx] : evt) {
				if (op == -1) ls.erase(find(ls.begin(), ls.end(), idx));
				else if (op == 1) ls.push_back(idx);
				else {
					for (auto l : ls) {
						ll dx = v[l].first - v[idx].first;
						ll dy = v[l].second - v[idx].second;
						ans[l] = min(ans[l], dx * dx + dy * dy);
					}
				}
			}
		};

		auto f = [&](auto &&f, int s, int e) {
			if (e - s + 1 <= 1) return;
			int m = s + e >> 1;
			f(f, s, m);
			f(f, m + 1, e);
			ll xm = xs[m].first;
			upd(s, m, m + 1, e, xm);
			upd(m + 1, e, s, m, xm);
		};
		f(f, 0, n - 1);

		for (int i = 0; i < n; i++) cout << ans[i] << "\n";
	}

	return 0;
}
