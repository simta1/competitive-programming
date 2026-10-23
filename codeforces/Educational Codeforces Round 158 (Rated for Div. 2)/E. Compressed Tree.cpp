#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void chmax(ll &a, ll b) {
	a = max(a, b);
}

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;

		vector<int> v(n);
		for (auto &e : v) cin >> e;

		vector<vector<int>> adj(n);
		for (int i = 1; i < n; i++) {
		    int u, v;
		    cin >> u >> v;
			--u, --v;
		    adj[u].push_back(v);
		    adj[v].push_back(u);
		}

		constexpr ll INF = 1e18;
		ll ans = 0;
		auto dfs = [&](auto &&dfs, int cur, int par) -> ll {
			ll sum[4] = {0, -INF, -INF, -INF};
			for (auto nxt : adj[cur]) if (nxt != par) {
				ll nres = dfs(dfs, nxt, cur);
				for (int cnt = 3; cnt >= 0; cnt--) chmax(sum[min(3, cnt + 1)], sum[cnt] + nres);
			}

			ll res = -INF;
			for (int cnt = 0; cnt < 4; cnt++) {
				chmax(res, sum[cnt] + (cnt + 1 == 2 ? 0 : v[cur]));
				chmax(ans, sum[cnt] + (cnt == 2 ? 0 : v[cur]));
			}
			return res;
		};
		dfs(dfs, 1, -1);
		cout << ans << "\n";
	}

	return 0;
}
