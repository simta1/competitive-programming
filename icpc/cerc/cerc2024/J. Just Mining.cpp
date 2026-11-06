#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename C, typename F>
struct Graph {
	struct Edge {
		int to, rev;
		F c, oc;
		C cost;
		int from;
	};
	vector<vector<Edge>> adj;
	C DIST_INF = numeric_limits<C>::max();
	Graph(int n) : adj(n) {} // 0-based
	void addEdge(int a, int b, C cost, F c) {
		adj[a].push_back({b, adj[b].size(), c, c, cost, a});
		adj[b].push_back({a, adj[a].size() - 1, 0, 0, -cost, b});
	}
	pair<C, F> mcmf(int s, int t, F targetFlow = numeric_limits<F>::max()) { // O(VEf) // average O(Ef)
		C minCost = 0;
		F maxFlow = 0;
		vector<Edge *> pedge(adj.size());
		vector<C> dist(adj.size());
		vector<bool> inq(adj.size());
		while (maxFlow < targetFlow) {
			fill(dist.begin(), dist.end(), DIST_INF);
			dist[s] = 0;
			queue<int> q;
			q.push(s);
			inq[s] = true;
			while (!q.empty()) {
				int cur = q.front();
				q.pop();
				inq[cur] = false;
				for (auto &e : adj[cur]) if (e.c && dist[e.to] > dist[cur] + e.cost) {
					dist[e.to] = dist[cur] + e.cost;
					pedge[e.to] = &e;
					if (!inq[e.to]) {
						q.push(e.to);
						inq[e.to] = true;
					}
				}
			}
			if (dist[t] >= 0) break;
			F f = targetFlow - maxFlow;
			for (Edge *e = pedge[t]; e; e = pedge[e->from]) f = min(f, e->c);
			for (Edge *e = pedge[t]; e; e = pedge[e->from]) {
				e->c -= f;
				adj[e->to][e->rev].c += f;
			}
			minCost += f * dist[t];
			maxFlow += f;
		}
		return {minCost, maxFlow};
	}
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<array<ll, 5>> v(n); // {x, y, r, f, idx}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) cin >> v[i][j];
		v[i][4] = i;
	}
	sort(v.begin(), v.end(), [&](auto a, auto b) {
		return a[2] < b[2];
	});

	auto laminar = [&](int i, int j) {
		auto [x1, y1, r1, f1, idx1] = v[i];
		auto [x2, y2, r2, f2, idx2] = v[j];
		ll dx = x2 - x1, dy = y2 - y1;
		ll dsq = dx * dx + dy * dy;
		return dsq > (r1 + r2) * (r1 + r2) || dsq < (r1 - r2) * (r1 - r2);
	};
	auto in = [&](int i, int j) {
		auto [x1, y1, r1, f1, idx1] = v[i];
		auto [x2, y2, r2, f2, idx2] = v[j];
		ll dx = x2 - x1, dy = y2 - y1;
		ll dsq = dx * dx + dy * dy;
		return dsq < (r1 - r2) * (r1 - r2);
	};

	vector<int> color(n, -1);
	for (int i = 0; i < n; i++) if (!~color[i]) {
		queue<int> q;
		q.push(i);
		color[i] = 0;
		while (!q.empty()) {
			auto cur = q.front();
			q.pop();
			for (int nxt = 0; nxt < n; nxt++) if (cur != nxt && !laminar(cur, nxt) && !~color[nxt]) {
				color[nxt] = !color[cur];
				q.push(nxt);
			}
		}
	}

	vector<int> p(n, -1);
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			if (color[j] == color[i] && in(i, j)) {
				p[i] = j;
				break;
			}
		}
	}

	int s = n + m, t = n + m + 1;
	Graph<ll, int> graph(t + 1);
	for (int i = 0; i < n; i++) {
		if (color[i]) {
			graph.addEdge(!~p[i] ? s : p[i], i, 0, v[i][3]);
		}
		else {
			graph.addEdge(i, !~p[i] ? t : p[i], 0, v[i][3]);
		}
	}

	vector<pair<int, int>> ref(m);
	for (int i = 0; i < m; i++) {
		ll x, y, val;
		cin >> x >> y >> val;
		bool visited[2]{};
		for (int j = 0; j < n; j++) {
			auto [cx, cy, r, f, idx] = v[j];
			ll dx = cx - x, dy = cy - y;
			if (dx * dx + dy * dy <= r * r) if (!visited[color[j]]) {
				if (color[j]) {
					ref[i] = {j, graph.adj[j].size()};
					graph.addEdge(j, n + i, -val, 1);
				}
				else graph.addEdge(n + i, j, 0, 1);
				visited[color[j]] = 1;
			}
		}
		if (!visited[1]) {
			ref[i] = {s, graph.adj[s].size()};
			graph.addEdge(s, n + i, -val, 1);
		}
		if (!visited[0]) graph.addEdge(n + i, t, 0, 1);
	}

	auto [mc, mf] = graph.mcmf(s, t);
	vector<int> ans;
	for (int i = 0; i < m; i++) {
		auto [a, b] = ref[i];
		if (!graph.adj[a][b].c) ans.push_back(i + 1);
	}

	cout << -mc << "\n";
	cout << ans.size() << "\n";
	for (auto e : ans) cout << e << " ";

	return 0;
}
