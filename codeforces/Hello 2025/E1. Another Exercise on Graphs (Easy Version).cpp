#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m, q;
        cin >> n >> m >> q;

        constexpr int INF = 1e8;
        vector dist(m + 1, vector(n + 1, vector<int>(n + 1, INF)));
        for (int i = 1; i <= n; i++) dist[0][i][i] = 0;

        vector<array<int, 3>> edges(m);
        for (auto &[w, u, v] : edges) {
            cin >> u >> v >> w;
            dist[0][u][v] = dist[0][v][u] = 1;
        }

        for (int m = 1; m <= n; m++) {
            for (int s = 1; s <= n; s++) {
                for (int e = 1; e <= n; e++) {
                    dist[0][s][e] = min(dist[0][s][e], dist[0][s][m] + dist[0][m][e]);
                }
            }
        }

        sort(edges.begin(), edges.end());
        for (int i = 1; i <= m; i++) {
            auto [w, u, v] = edges[i - 1];
            dist[i] = dist[i - 1];
            for (int s = 1; s <= n; s++) {
                for (int e = 1; e <= n; e++) {
                    dist[i][s][e] = min({
                        dist[i][s][e],
                        dist[i - 1][s][u] + dist[i - 1][v][e],
                        dist[i - 1][s][v] + dist[i - 1][u][e]
                    });
                }
            }
        }

        while (q--) {
            int a, b, k;
            cin >> a >> b >> k;

            int lo = 0, hi = m;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                if (dist[mid][a][b] <= k - 1) hi = mid;
                else lo = mid;
            }
            cout << edges[hi - 1][0] << " ";
        }
        cout << "\n";
    }

    return 0;
}
