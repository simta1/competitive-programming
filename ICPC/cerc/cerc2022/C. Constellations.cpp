#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll d, s;
    int ti, tj, i, j;
    bool operator<(const Node &o) const { // >로 생각
        // d/s > o.d/o.s
        if (d * o.s != o.d * s) return d * o.s > o.d * s;
        if (ti != o.ti) return ti > o.ti;
        return tj > o.tj;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> p(n), t(n), sz(n, 1);
    iota(p.begin(), p.end(), 0);
    iota(t.begin(), t.end(), 0);

    auto find = [&](int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    };

    vector<pair<ll, ll>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    vector dsum(n, vector<ll>(n, 0));
    vector ssum(n, vector<ll>(n, 0));

    priority_queue<Node> pq;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll dx = v[i].first - v[j].first;
            ll dy = v[i].second - v[j].second;
            dsum[i][j] = dsum[j][i] = dx * dx + dy * dy;
            ssum[i][j] = ssum[j][i] = 1;
            // cout << dsum[i][j] << " " << i << " " << j << "--\n";
            pq.push({dsum[i][j], ssum[i][j], t[i], t[j], i, j});
        }
    }

    int curt = n;
    while (!pq.empty()) {
        auto [dij, sij, ti, tj, i, j] = pq.top();
        // cout << pq.size() << "::\n";
        pq.pop();
        if (ti != t[find(i)] || tj != t[find(j)]) continue;
        // cout << dij << " " << sij << " " << ti << " " << tj << " " << i << " " << j << "::\n";
        
        i = find(i);
        j = find(j);
        p[i] = j;
        t[j] = curt++;
        sz[j] += sz[i];

        cout << sz[j] << "\n";

        dsum[i][j] = 0;
        for (int k = 0; k < n; k++) {
            if (j == find(k)) continue;
            dsum[j][k] = dsum[k][j] = dsum[i][k] + dsum[j][k];
            ssum[j][k] = ssum[k][j] = ssum[i][k] + ssum[j][k];
            pq.push({dsum[j][k], ssum[j][k], t[k], t[j], k, j});
        }
    }

    return 0;
}
