#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	int to = n;

	vector<int> p(n + 1);
	iota(p.begin(), p.end(), 0);
	auto find = [&](int a) {
		while (a != p[a]) a = p[a] = p[p[a]];
		return a;
	};
	auto merge = [&](int a, int b) {
		p[find(a)] = find(b);
	};

	vector<int> visited(n + 1);
	int tv = 0;

	vector<vector<pair<int, int>>> adj(n + 1);
	auto addEdge = [&](int u, int v, int w) {
		adj[u].emplace_back(v, w);
	};

	vector<array<int, 3>> edges(m);
	for (auto &[c, u, v] : edges) cin >> u >> v >> c;
	sort(edges.begin(), edges.end());
	for (int i = 0, j = 0; i < m; i = j) {
		while (j < m && edges[i][0] == edges[j][0]) ++j;

		vector<int> dirt;
		for (int k = i; k < j; k++) {
			auto [_, u, v] = edges[k];
			dirt.push_back(u);
			dirt.push_back(v);
			merge(u, v);
		}

		++tv;
		map<int, int> mp;
		for (auto e : dirt) if (visited[e] != tv) {
			visited[e] = tv;
			int x = find(e);
			if (!mp.count(x)) {
				mp[x] = ++n;
				adj.emplace_back();
			}
			int node = mp[x];
			addEdge(e, node, 1);
			addEdge(node, e, 0);
		}

		for (auto e : dirt) p[e] = e;
	}

	deque<int> dq;
	dq.push_back(1);
	constexpr int INF = 1e8;
	vector<int> dist(n + 1, INF);
	dist[1] = 0;

	while (!dq.empty()) {
		auto cur = dq.front();
		dq.pop_front();
		for (auto [nxt, cost] : adj[cur]) {
			int ndist = dist[cur] + cost;
			if (dist[nxt] > ndist) {
				dist[nxt] = ndist;
				if (cost) dq.push_back(nxt);
				else dq.push_front(nxt);
			}
		}
	}

	int ans = dist[to];
	if (ans == INF) cout << -1;
	else cout << ans;

	return 0;
}
