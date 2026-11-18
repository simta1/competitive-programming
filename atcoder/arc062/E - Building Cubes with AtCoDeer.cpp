#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<array<int, 4>> v(n);
	for (auto &[a, b, c, d] : v) cin >> a >> b >> c >> d;

	auto norm = [&](const array<int, 4> &a) {
		auto res = a;
		for (int i = 1; i < 4; i++) {
			auto cur = a;
			rotate(cur.begin(), cur.begin() + i, cur.end());
			res = min(res, cur);
		}
		return res;
	};
	auto f = [&](const array<int, 4> &a) {
		int res = 1;
		for (int i = 1; i < 4; i++) {
			auto cur = a;
			rotate(cur.begin(), cur.begin() + i, cur.end());
			res += cur == a;
		}
		return res;
	};

	map<array<int, 4>, int> mp;
	for (auto &e : v) {
		e = norm(e);
		++mp[e];
	}

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int d = 0; d < 4; d++) {
				ll res = 1;
				array<int, 4> used[4]{};
				for (int k = 0; k < 4; k++) {
					int c0 = v[i][(k + 1) & 3], c1 = v[i][k];
					int c2 = v[j][(d - k + 4) & 3], c3 = v[j][(d - k + 3) & 3];

					auto cur = norm({c0, c1, c2, c3});
					int cnt = mp.count(cur) ? mp[cur] : 0;
					cnt -= cur == v[i];
					cnt -= cur == v[j];
					for (int pk = 0; pk < k; pk++) cnt -= cur == used[pk];
					used[k] = cur;
					res *= cnt * f(cur);
				}
				
				ans += res;
			}
		}
	}
	cout << ans / 3;

	return 0;
}
