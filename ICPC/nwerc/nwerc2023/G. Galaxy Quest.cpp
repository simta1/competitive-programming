#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    vector<array<int, 3>> v(n);
    for (auto &[x, y, z] : v) cin >> x >> y >> z;

    using ld = double;
    auto f = [&](const array<int, 3> &a, const array<int, 3> &b) {
        ld res = 0;
        for (int i = 0; i < 3; i++) res += (a[i] - b[i]) * (a[i] - b[i]);
        return pow(res, 0.25);
    };

    vector<vector<pair<int, ld>>> adj(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        ld w = f(v[a], v[b]);
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }

    using elem = pair<ld, int>;
    priority_queue<elem, vector<elem>, greater<elem>> pq;
    const ld INF = 1/.0;
    vector<ld> dist(n, INF);
    dist[0] = 0;
    pq.emplace(dist[0], 0);
    while (!pq.empty()) {
        auto [distance, cur] = pq.top();
        pq.pop();
        if (distance > dist[cur]) continue;
        for (auto [nxt, cost] : adj[cur]) if (dist[nxt] > dist[cur] + cost) {
            dist[nxt] = dist[cur] + cost;
            pq.emplace(dist[nxt], nxt);
        }
    }

    cout << fixed << setprecision(12);
    while (q--) {
        int c, t;
        cin >> c >> t;
        --c;
        ld D = dist[c];
        if (D == INF || 2 * D > t) {
            cout << "impossible\n";
            continue;
        }

        cout << t - sqrt(t * t - 4 * D * D) << "\n";
    }

    return 0;
}
