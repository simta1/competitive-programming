#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	constexpr ll INF = 1e16;
	vector dist(n, vector<ll>(n, INF));
	for (int i = 0; i < n; i++) dist[i][i] = 0;

	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		dist[u][v] = min<ll>(dist[u][v], w);
	}

	for (int m = 0; m < n; m++) {
		for (int s = 0; s < n; s++) {
			for (int e = 0; e < n; e++) {
				if (dist[s][m] == INF || dist[m][e] == INF) continue;
				dist[s][e] = min(dist[s][e], dist[s][m] + dist[m][e]);
			}
		}
	}
	// for (int i = 0; i < n; i++) assert(dist[i][i] >= 0);

	vector dp(1 << n, vector<ll>(n, INF));
	for (int i = 0; i < n; i++) dp[1 << i][i] = 0;

	for (int mask = 1; mask < (1 << n); mask++) {
		for (int cur = 0; cur < n; cur++) if (mask >> cur & 1) {
			if (dp[mask][cur] == INF) continue;

			for (int nxt = 0; nxt < n; nxt++) if (~mask >> nxt & 1) {
				if (dist[cur][nxt] == INF) continue;
				int nmask = mask | 1 << nxt;
				dp[nmask][nxt] = min(dp[nmask][nxt], dp[mask][cur] + dist[cur][nxt]);
			}
		}
	}

	int mask = (1 << n) - 1;
	ll ans = *min_element(dp[mask].begin(), dp[mask].end());
	if (ans == INF) cout << "No";
	else cout << ans;

	return 0;
}
