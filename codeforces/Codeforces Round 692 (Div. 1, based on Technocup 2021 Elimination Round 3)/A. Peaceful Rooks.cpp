#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int TC;
	for (cin >> TC; TC--;) {
		int n, m;
		cin >> n >> m;

		vector<pair<int, int>> v(m);
		vector<vector<int>> adj(n + 1);
		for (int i = 0; i < m; i++) {
			auto &[x, y] = v[i];
			cin >> x >> y;
			adj[x].push_back(i);
			adj[y].push_back(i);
		}

		vector<bool> visited(m);
		vector<bool> used(n + 1);
		int ans = 0;
		for (int i = 0; i < m; i++) if (!visited[i] && v[i].first != v[i].second) {
			queue<int> q;
			visited[i] = 1;
			q.push(i);
			int rook = 0, cnt = 0;
			
			while (!q.empty()) {
				auto cur = q.front();
				q.pop();
				auto [x, y] = v[cur];

				++rook;
				if (!used[x]) {
					used[x] = 1;
					++cnt;
				}
				if (!used[y]) {
					used[y] = 1;
					++cnt;
				}

				for (auto nxt : adj[x]) if (!visited[nxt]) {
					visited[nxt] = 1;
					q.push(nxt);
				}
				for (auto nxt : adj[y]) if (!visited[nxt]) {
					visited[nxt] = 1;
					q.push(nxt);
				}
			}

			// cout << v[i].first << " " << v[i].second << " " << rook << " " << cnt << "::\n";

			if (rook < cnt) ans += rook;
			else ans += rook + 1;
		}
		cout << ans << "\n";
	}

	return 0;
}
