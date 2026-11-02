#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n;
	cin >> n;

	vector<vector<int>> adj(n + 1);
	for (int i = 1; i < n; i++) {
	    int u, v;
	    cin >> u >> v;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}

	vector<int> down(n + 1);
	auto dfs = [&](auto &&dfs, int cur, int par) -> void {
		int mx = 0;
		for (auto nxt : adj[cur]) if (nxt != par) {
			dfs(dfs, nxt, cur);
			mx = max(mx, down[nxt] + 1);
		}
		down[cur] = mx;
	};
	dfs(dfs, 1, -1);

	vector<int> up(n + 1), dp(n + 1);
	auto dfs2 = [&](auto &&dfs2, int cur, int par) -> void {
		vector<int> pref(adj[cur].size());
		for (int i = 0; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (nxt == par) pref[i] = up[cur] + 1;
			else pref[i] = down[nxt] + 1;
		}
		auto suf = pref;
		for (int i = 1; i < pref.size(); i++) pref[i] = max(pref[i - 1], pref[i]);
		for (int i = suf.size() - 2; i >= 0; i--) suf[i] = max(suf[i + 1], suf[i]);

		dp[cur] = pref.empty() ? 0 : pref.back();

		for (int i = 0; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (nxt != par) {
				up[nxt] = max(i ? pref[i - 1] : 0, i + 1 < adj[cur].size() ? suf[i + 1] : 0);
				dfs2(dfs2, nxt, cur);
			}
		}
	};
	dfs2(dfs2, 1, -1);

	for (int i = 1; i <= n; i++) cout << dp[i] << " ";

	return 0;
}
