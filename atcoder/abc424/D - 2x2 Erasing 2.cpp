#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<int> v(n + 1);
		for (int i = 1; i <= n; i++) {
			string st;
			cin >> st;
			for (int j = 0; j < m; j++) if (st[j] == '#') v[i] |= 1 << j;
		}

		int M = 1 << m;
		constexpr int INF = 1e8;
		vector<int> dp(M, INF);
		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			vector<int> ndp(M, INF);
			for (int mask = 0; mask < M; mask++) {
				if (dp[mask] == INF) continue;
				for (int nmask = 0; nmask < M; nmask++) if ((nmask & v[i]) == nmask) {
					int prv = v[i - 1] ^ mask;
					int cur = v[i] ^ nmask;
					int chk = prv & cur;
					// for (int i = 1; i < m; i++)
					if (__builtin_popcount((chk >> 1) & chk)) continue;
					ndp[nmask] = min(ndp[nmask], dp[mask] + __builtin_popcount(nmask));
				}
			}
			swap(dp, ndp);
		}
		cout << *min_element(dp.begin(), dp.end()) << "\n";
	}

	return 0;
}
