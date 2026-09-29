#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    constexpr int INF = 1e8;
    vector dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    vector<vector<int>> adj(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dist[u][v] = dist[v][u] = 1;
    }

    for (int m = 0; m < n; m++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                dist[s][e] = min(dist[s][e], dist[s][m] + dist[m][e]);
            }
        }
    }

    constexpr ll MOD = 998'244'353;
    
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            int d = dist[x][y], cnt = 0;
            for (int i = 0; i < n; i++) {
                cnt += dist[i][x] + dist[i][y] == d;
            }

            ll ans = 0;
            if (cnt == d + 1) {
                ans = 1;
                for (int i = 0; i < n; i++) if (dist[i][x] + dist[i][y] > d) {
                    int cnt = 0;
                    for (auto j : adj[i]) {
                        cnt += (dist[j][x] + 1 == dist[i][x] && dist[j][y] + 1 == dist[i][y]);
                    }
                    ans = ans * cnt % MOD;
                }
            }
            cout << ans << " ";
        }
        cout << "\n";
    }

    return 0;
}
