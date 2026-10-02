#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		ll k;
		cin >> n >> k;

		vector<int> qs(n), rs(n);
		for (auto &e : qs) cin >> e;
		for (auto &e : rs) cin >> e;
		sort(qs.rbegin(), qs.rend());
		sort(rs.rbegin(), rs.rend());

		int ans = 0;
		for (auto r : rs) {
			ll mxq = (k - r) / (r + 1);

			if (!qs.empty() && qs.back() <= mxq) {
				qs.pop_back();
				++ans;
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
