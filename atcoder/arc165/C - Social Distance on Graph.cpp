#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	constexpr int INF = 2e9;
	vector<int> mn(n + 1, INF), mn2(n + 1, INF);
	auto upd = [&](int node, int w) {
		if (mn[node] > w) swap(mn[node], w);
		if (mn2[node] > w) swap(mn2[node], w);
	};

	vector<vector<pair<int, int>>> adj(n + 1);
	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;
		upd(u, w);
		upd(v, w);
	    adj[u].emplace_back(v, w);
	    adj[v].emplace_back(u, w);
	}

	int hi = INF;
	for (int i = 1; i <= n; i++) if (mn2[i] != INF) {
		hi = min(hi, mn[i] + mn2[i]);
	}
	++hi;

	auto check = [&](int x) {
		vector<int> visited(n + 1);
		queue<int> q;
		for (int i = 1; i <= n; i++) if (!visited[i]) {
			visited[i] = 1;
			q.push(i);

			while (!q.empty()) {
				auto cur = q.front();
				q.pop();
				for (auto [nxt, cost] : adj[cur]) if (cost < x) {
					if (!visited[nxt]) {
						visited[nxt] = 3 - visited[cur];
						q.push(nxt);
					}
					else {
						if (visited[nxt] != 3 - visited[cur]) return false;
					}
				}
			}
		}
		return true;
	};

	int lo = 0;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo;

	return 0;
}
