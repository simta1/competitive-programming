#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout << fixed << setprecision(12);

	int TC;
	for (cin >> TC; TC--;) {
		int n, k, x;
		cin >> n >> k >> x;
		x = n + k + 1 - x;

		vector<ll> v(n);
		for (auto &e : v) {
			cin >> e;
			e <<= 30;
		}
		sort(v.rbegin(), v.rend());
		
		auto check = [&](ll mid) {
			ll cnt = 0;
			for (auto e : v) {
				if (e > mid) {
					ll x = (e - 1) / mid;
					int lg = 0;
					while ((1LL << lg) <= x) ++lg;
					cnt += (1LL << lg) - 1;
				}
			}
			return cnt <= k;
		};

		ll lo = 0, hi = 4e18;
		while (lo + 1 < hi) {
			ll mid = (lo + hi) / 2;
			if (check(mid)) hi = mid;
			else lo = mid;
		}

		ll len = hi;
		map<ll, int> mp;
		for (auto e : v) {
			if (e > len) {
				ll x = (e - 1) / len;
				int lg = 0;
				while ((1 << lg) <= x) ++lg;
				k -= (1 << lg) - 1;
				mp[e / (1 << lg)] += 1 << lg;
			}
			else ++mp[e];
		}

		if (k) {
			auto it = prev(mp.end());
			auto [val, cnt] = *it;
			assert(cnt >= k);
			it->second -= k;
			mp[val / 2] += 2 * k;
		}

		for (auto [val, cnt] : mp) {
			x -= cnt;
			if (x <= 0) {
				cout << val / double(1 << 30) << "\n";
				break;
			}
		}
	}

	return 0;
}
