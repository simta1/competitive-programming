#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	cin.tie(0) -> sync_with_stdio(0);

	while (1) {
		int H;
		cin >> H;
		if (!H) break;

		vector<vector<int>> id(2 * H - 1);
		int t = 0;
		int N = 3 * H * (H - 1) + 1;
		vector<int> v(N);
		constexpr int INF = 1e8;
		vector dp(16, vector<int>(N, INF));
		for (int i = 0; i < 2 * H - 1; i++) {
			int len = i < H ? (H + i) : (2 * H - 1 - (i - H + 1));
			id[i].resize(len);
			for (int j = 0; j < len; j++) {
				char ch;
				cin >> ch;
				if (ch != '.') dp[1 << ch - 'A'][t] = 0;
				else v[t] = 1;
				id[i][j] = t++;
			}
		}

		vector<vector<int>> adj(t);
		auto addEdge = [&](int u, int v) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		};

		for (int i = 0; i < 2 * H - 1; i++) {
			int len = i < H ? (H + i) : (2 * H - 1 - (i - H + 1));
			for (int j = 1; j < len; j++) addEdge(id[i][j - 1], id[i][j]);
		}

		for (int i = 0; i + 1 < H; i++) {
			int len = H + i;
			for (int j = 0; j < len; j++) {
				addEdge(id[i][j], id[i + 1][j]);
				addEdge(id[i][j], id[i + 1][j + 1]);

				addEdge(id[2 * H - 2 - i][j], id[2 * H - 2 - i - 1][j]);
				addEdge(id[2 * H - 2 - i][j], id[2 * H - 2 - i - 1][j + 1]);
			}
		}

		auto dijkstra = [&](int s) {
			vector<int> dist(N, INF);
			dist[s] = 0;
			using elem = pair<int, int>;
			priority_queue<elem, vector<elem>, greater<elem>> pq;
			pq.emplace(dist[s], s);
			while (!pq.empty()) {
				auto [distance, cur] = pq.top();
				pq.pop();
				if (distance > dist[cur]) continue;
				for (auto nxt : adj[cur]) if (dist[nxt] > dist[cur] + v[nxt]) {
					dist[nxt] = dist[cur] + v[nxt];
					pq.emplace(dist[nxt], nxt);
				}
			}
			return dist;
		};
		vector<vector<int>> dist(N);
		for (int i = 0; i < N; i++) dist[i] = dijkstra(i);

		for (int mask = 1; mask < 16; mask++) {
			if (__builtin_popcount(mask) > 1) {
				for (int x = 0; x < N; x++) {
					for (int sub = 1; sub < mask; sub++) if ((sub & mask) == sub) {
						dp[mask][x] = min(dp[mask][x], dp[sub][x] + dp[mask ^ sub][x] - v[x]);
					}
				}
			}

			for (int x = 0; x < N; x++) {
				for (int y = 0; y < N; y++) {
					dp[mask][x] = min(dp[mask][x], dp[mask][y] + dist[y][x]);
				}
			}
		}

		cout << "You have to buy " << *min_element(dp[15].begin(), dp[15].end()) << " parcels.\n";
	}

	return 0;
}
