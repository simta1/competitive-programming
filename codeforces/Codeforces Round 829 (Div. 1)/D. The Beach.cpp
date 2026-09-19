#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int p, q;
    cin >> p >> q;

    vector<string> v(n);
    for (auto &st : v) cin >> st;

    constexpr ll INF = 1e18;
    vector dist(n, vector<ll>(m, INF));
    using elem = tuple<ll, int, int>;
    priority_queue<elem, vector<elem>, greater<elem>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == '.') {
                dist[i][j] = 0;
                pq.push({0, i, j});
            }
        }
    }

    auto inRange = [&](int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < m;
    };

    vector<tuple<int, int, char, int>> dpos = {
        {1, 1, 'D', p}, {1, 1, 'R', p},
        {1, -1, 'D', p}, {1, -1, 'L', p},
        {-1, 1, 'U', p}, {-1, 1, 'R', p},
        {-1, -1, 'U', p}, {-1, -1, 'L', p},
        {0, 2, 'R', q}, {0, -2, 'L', q}, {2, 0, 'D', q}, {-2, 0, 'U', q}
    };

    while (!pq.empty()) {
        auto [distance, ci, cj] = pq.top();
        pq.pop();
        if (distance > dist[ci][cj]) continue;

        for (auto [di, dj, ch, cost] : dpos) {
            int ni = ci + di;
            int nj = cj + dj;

            // if (ci == 0 && cj == 0) {
            //     if (ni == 0 && nj == 2) cout << "O\n";
            //     else cout << "X\n";
            // }

            if (inRange(ni, nj) && v[ni][nj] == ch && dist[ni][nj] > dist[ci][cj] + cost) {
                dist[ni][nj] = dist[ci][cj] + cost;
                pq.push({dist[ni][nj], ni, nj});
            }
        }
    }
    // cout << dist[0][2] << " " << dist[1][2] << "\n";

    ll ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            ans = min(ans, dist[i][j - 1] + dist[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = min(ans, dist[i - 1][j] + dist[i][j]);
        }
    }

    if (ans == INF) cout << -1;
    else cout << ans;

    return 0;
}
