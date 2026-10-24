#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n;
		cin >> n;
		vector<pair<int, int>> a(n);
		for (int i = 0; i < n; i++) cin >> a[i].first;
		for (int i = 0; i < n; i++) cin >> a[i].second;

		int m;
		cin >> m;
		vector<pair<int, int>> b(m);
		for (int i = 0; i < m; i++) cin >> b[i].first;
		for (int i = 0; i < m; i++) cin >> b[i].second;

		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		auto v = a;
		for (int i = n - 2; i >= 0; i--) a[i].second = max(a[i].second, a[i + 1].second);
		for (int i = m - 2; i >= 0; i--) b[i].second = max(b[i].second, b[i + 1].second);

		vector<int> who;
		map<pair<bool, int>, int> mp;
		auto f = [&](bool a, int b) {
			if (!mp.count({a, b})) {
				mp[{a, b}] = who.size();
				who.push_back(a);
			}
			return mp[{a, b}];
		};

		int N = n + m;
		vector<int> adj(N, -1);
		auto addEdge = [&](int u, int v) {
			// cout << u << " " << v << "::\n";
			// assert(u < N);
			adj[u] = v;
		};

		constexpr int INF = 1e8;
		for (int i = 0; i < n; i++) {
			auto it = upper_bound(b.begin(), b.end(), pair{v[i].second, INF});
			if (it != b.end()) addEdge(f(0, v[i].second), f(1, it->second));
		}
		for (int i = 0; i < m; i++) {
			auto it = upper_bound(a.begin(), a.end(), pair{b[i].second, INF});
			if (it != a.end()) addEdge(f(1, b[i].second), f(0, it->second));
		}

		vector<int> state(N), dp(N, -1);
		auto dfs = [&](auto &&dfs, int cur) -> void {
			state[cur] = 1;
			int nxt = adj[cur];
			if (!~nxt) {
				dp[cur] = (who[cur] == 0 ? 0 : 2);
			}
			else {
				if (!state[nxt]) {
					dfs(dfs, nxt);
					dp[cur] = dp[nxt];
				}
				else if (state[nxt] == 2) {
					dp[cur] = dp[nxt];
				}
				else {
					dp[cur] = 1;
				}
			}
			state[cur] = 2;
		};

		int ans[3]{};
		for (int i = 0; i < n; i++) {
			int cur = f(0, v[i].second);
			if (!state[cur]) dfs(dfs, cur);
			++ans[dp[cur]];
		}

		for (int i = 0; i < 3; i++) cout << ans[i] << " ";
		cout << "\n";
	}

	return 0;
}
