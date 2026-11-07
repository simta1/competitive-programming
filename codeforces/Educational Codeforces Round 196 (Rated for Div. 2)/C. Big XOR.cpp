#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		if (n <= 2) {
			for (int i = 1; i <= n; i++) cout << "1 ";
			cout << "\n";
			continue;
		}

		vector<bool> ans(n + 1);
		int osum = 0, xsum = 0;
		for (int i = 1; i <= n; i++) {
			osum |= i;
			xsum ^= i;
		}
		int cur = (osum << 1) ^ xsum;

		for (int i = n; i >= 1; i--) {
			int nxt = cur ^ i ^ (2 * i);
			if (nxt < cur) {
				cur = nxt;
				ans[i] = 1;
			}
		}

		// int cnt = __builtin_popcount(target);
		// if (cnt & 1) {
		// 	target |= 1;
		// 	++cnt;
		// }

		// // cout << target << "\n";
		// int l = -1;
		// for (int i = 0; i < 20; i++) if (target >> i & 1) {
		// 	if (!~l) {
		// 		l = i;
		// 	}
		// 	else {
		// 		int r = i;
		// 		int mask = 0;
		// 		for (int k = l; k < r; k++) mask |= 1 << k;
		// 		// cout << mask << "::\n";
		// 		ans[mask] = 1;
		// 		l = -1;
		// 	}
		// }

		for (int i = 1; i <= n; i++) cout << ans[i] << " ";
		cout << "\n";
	}

	return 0;
}
