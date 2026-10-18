#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, t, m;
    cin >> n >> t >> m;

    int s, e;
    cin >> s >> e;

    constexpr int INF = 1e8;
    vector<int> dist(n, INF);
    dist[s] = 0;

    while (t--) {
        auto ndist = dist;
        for (int _ = m; _--;) {
            int u, v, w;
            cin >> u >> v >> w;
            ndist[v] = min(ndist[v], dist[u] + w);
            ndist[u] = min(ndist[u], dist[v] + w);
        }
        swap(ndist, dist);
    }

    int ans = dist[e];
    if (ans == INF) cout << -1;
    else cout << ans;

    return 0;
}
