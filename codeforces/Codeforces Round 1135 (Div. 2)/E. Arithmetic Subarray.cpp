#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, k;
		cin >> n >> k;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		vector<int> right(n);
		right[n - 2] = n - 1;
		for (int i = n - 3; i >= 0; i--) {
			if (v[i + 1] - v[i] == v[i + 2] - v[i + 1]) right[i] = right[i + 1];
			else right[i] = i + 1;
		}

		auto f = [&](int l, int d) {
			int cnt = k;
			int cur = l;
			while (cur < n) {
				if (v[cur] - v[l] == ll(cur - l) * d) {
					if (cur + 1 < n && v[cur + 1] - v[cur] == d) cur = right[cur] + 1;
					else ++cur;
				}
				else {
					if (cnt) {
						--cnt;
						++cur;
					}
					else break;
				}
			}
			return min(n, cur - l + cnt);
		};

		int ans = min(n, k + 2);
		for (int l = 0; l + 1 < n; l++) {
			int mx = 0, mxd;
			map<int, int> mp;
			for (int i = l + 1; i < n; i++) {
				int diff = v[i] - v[l];
				int len = i - l;
				if (diff % len == 0) {
					int d = diff / len;
					int cur = ++mp[d];
					if (mx < cur) {
						mx = cur;
						mxd = d;
					}
				}

				if (i - l - mx > k) break;
				ans = max(ans, min(n, mx + 1 + k));
				if (mx > k) {
					ans = max(ans, f(l, mxd));
					break;
				}
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
