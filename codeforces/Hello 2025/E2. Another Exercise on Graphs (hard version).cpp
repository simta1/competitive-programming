#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    }
    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m, q;
        cin >> n >> m >> q;

        constexpr int INF = 1e8;
        vector dist(1, vector(n + 1, vector<int>(n + 1, INF)));
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

        DSU dsu(n + 1);
        sort(edges.begin(), edges.end());
        vector<int> ws;
        for (auto [w, u, v] : edges) {
            if (dsu.find(u) == dsu.find(v)) continue;
            dsu.merge(u, v);

            vector<vector<int>> d = dist.back();
            for (int s = 1; s <= n; s++) {
                for (int e = 1; e <= n; e++) {
                    d[s][e] = min({
                        d[s][e],
                        d[s][u] + d[v][e],
                        d[s][v] + d[u][e]
                    });
                }
            }
            dist.push_back(d);
            ws.push_back(w);
        }

        while (q--) {
            int a, b, k;
            cin >> a >> b >> k;

            int lo = 0, hi = dist.size() - 1;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                if (dist[mid][a][b] <= k - 1) hi = mid;
                else lo = mid;
            }
            cout << ws[hi - 1] << " ";
        }
        cout << "\n";
    }

    return 0;
}
