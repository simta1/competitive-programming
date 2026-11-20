#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	while (1) {
		int n, m;
		cin >> n >> m;
		if (!n && !m) break;

		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			string st;
			cin >> st;
			for (int j = 0; j < m; j++) if (st[j] == 'X') v[i] |= 1 << j;
		}

		constexpr int INF = 1e8;
		const int FULL = (1 << m) - 1;
		int ans = INF;
		for (int mask = 0; mask < (1 << m); mask++) {
			int prv = 0, cur = mask, sum = 0;

			for (int i = 0; i < n; i++) {
				sum += __builtin_popcount(cur);
				int nxt = (
					v[i] ^ prv ^ cur ^ (cur << 1) ^ (cur >> 1)
				) & FULL;
				prv = cur;
				cur = nxt;
			}
			if (cur == 0) ans = min(ans, sum);
		}

		if (ans == INF) cout << "Damaged billboard.\n";
		else cout << "You have to tap " << ans << " tiles.\n";
	}

	return 0;
}
