#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	constexpr int MX = 1e6;
	static ll tri[MX + 5];
	for (int i = 1; i < MX + 5; i++) tri[i] = tri[i - 1] + i;
	// k번째 구간: (tri[k]-k:tre[k]]

	auto getK = [&](ll x) {
		int k = ceil((sqrt(1 + 8 * x) - 1) / 2);
		while (k > 0 && x <= tri[k - 1]) --k;
		while (tri[k] < x) ++k;
		return k;
	};

	int n;
	cin >> n;

	vector<int> v(n);
	for (auto &e : v) cin >> e;
	for (int k1 = 1; k1 <= 1'000'001; k1 += 2) {
		ll l1 = tri[k1 - 1] + 1;
		ll r1 = tri[k1];
		if (r1 < v[0]) continue;
		ll dx1 = max(0LL, l1 - v[0]);
		ll dx2 = r1 - v[0];
		int mxk = getK(v.back() + dx2);
		for (int k = k1; k <= mxk; k++) {
			ll l = tri[k - 1] + 1;
			ll r = tri[k];
			// l <= v[i] + dx1 <= r
			auto it = lower_bound(v.begin(), v.end(), l - dx1);
			auto jt = upper_bound(v.begin(), v.end(), r - dx1);
			if (it == jt) continue;

			// l <= *it + dx1
			// *prev(jt) + dx2 <= r
			if (k & 1) {
				dx2 = min(dx2, r - *prev(jt));
			}
			else {
				l = tri[k] + 1;
				r = tri[k + 1];
				dx1 = max(dx1, l - *it);
				dx2 = min(dx2, r - *prev(jt));
			}
			if (dx1 > dx2) break;
		}
		if (dx1 <= dx2) {
			cout << dx1;
			return 0;
		}
	}

	assert(false);
}
