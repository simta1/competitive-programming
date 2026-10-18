#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto get_z(const string &st) {
    int n = st.size();
    vector<int> z(n);
    for (int i = 1, p = 0; i < n; i++) {
        if (p + z[p] > i) z[i] = min(p + z[p] - i, z[i - p]);
        while (i + z[i] < n && st[z[i]] == st[i + z[i]]) ++z[i];
        if (p + z[p] < i + z[i]) p = i;
    }
    z[0] = n;
    return z;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int m, n;
    string p, t;
    cin >> m >> n >> p >> t;

    auto z = get_z(p + "*" + t);

    using elem = array<int, 3>;
    priority_queue<elem, vector<elem>, greater<elem>> pq;
    constexpr int INF = 1e8;
    vector<array<int, 2>> dist(n + 1, {INF, INF});
    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [distance, cur, prv_rm] = pq.top();
        pq.pop();

        if (distance > dist[cur][prv_rm]) continue;

        vector<array<int, 3>> adj;
        if (cur < n && !prv_rm) adj.push_back({cur + 1, 1, 0});
        if (cur) adj.push_back({cur - 1, 1, 1});
        if (cur < n) {
            int len = z[m + 1 + cur];
            adj.push_back({cur + len, m - len, len < p.size()});
        }
        for (auto [nxt, cost, rm] : adj) {
            if (dist[nxt][rm] > dist[cur][prv_rm] + cost) {
                dist[nxt][rm] = dist[cur][prv_rm] + cost;
                pq.push({dist[nxt][rm], nxt, rm});
            }
        }
    }
    cout << dist[n][0];

    return 0;
}
