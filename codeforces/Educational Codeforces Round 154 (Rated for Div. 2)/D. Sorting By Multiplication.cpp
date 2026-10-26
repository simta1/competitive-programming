#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		vector<int> suf(n);
		for (int i = n - 2; i >= 0; i--) {
			suf[i] = suf[i + 1] + (v[i] >= v[i + 1]);
		}

		vector<int> pref(n);
		for (int i = 1; i < n; i++) {
			pref[i] = pref[i - 1] + (v[i - 1] <= v[i]);
		}

		int ans = min(suf[0], 1 + pref[n - 1]);
		for (int i = 1; i < n; i++) {
			if (v[i - 1] >= v[i]) {
				ans = min(ans, 1 + pref[i - 1] + suf[i]);
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
