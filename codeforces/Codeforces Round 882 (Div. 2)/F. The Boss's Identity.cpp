#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, q;
        cin >> n >> q;

        int osum = 0;
        vector<int> v(n);
        for (auto &e : v) cin >> e, osum |= e;

        int last[30];
        memset(last, -1, sizeof(last));
        vector<array<int, 30>> dist(n);
        constexpr int INF = 1e9;
        for (auto &r : dist) r.fill(INF);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 30; j++) if (v[i] >> j & 1) last[j] = i;
            for (int j = 0; j < 30; j++) if (~last[j]) dist[i][j] = i - last[j];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 30; j++) dist[i][j] = min(dist[i][j], i + n - last[j]);
        }

        vector<pair<int, ll>> a;
        for (int i = 0; i < n; i++) a.emplace_back(v[i], i);
        for (int i = 1; i < n; i++) {
            int cur = v[i];
            vector<pair<int, int>> evt;
            for (int j = 0; j < 30; j++) if (osum >> j & 1) if (dist[i][j] != INF) evt.emplace_back(dist[i][j], j);
            sort(evt.begin(), evt.end());
            for (int j = 0, k = 0; j < evt.size(); j = k) {
                while (k < evt.size() && evt[j].first == evt[k].first) ++k;
                for (int l = j; l < k; l++) cur |= 1 << evt[l].second;
                a.emplace_back(cur, i + evt[j].first * ll(n - 1));
            }
        }

        sort(a.begin(), a.end(), [&](pair<int, ll> &x, pair<int, ll> &y) {
            return x.second < y.second;
        });
        for (int i = 1; i < a.size(); i++) a[i].first = max(a[i].first, a[i - 1].first);

        while (q--) {
            int x;
            cin >> x;
            auto it = upper_bound(a.begin(), a.end(), pair{x, LLONG_MAX});
            if (it == a.end()) cout << "-1\n";
            else cout << it->second + 1 << "\n";
        }
    }

    return 0;
}
