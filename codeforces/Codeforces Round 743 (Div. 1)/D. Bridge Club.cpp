#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> v(1 << n);
    for (auto &e : v) cin >> e;

    priority_queue<array<int, 3>> pq;
    for (int l = 0; l < (1 << n); l++) if (__builtin_popcount(l) & 1) {
        for (int i = 0; i < n; i++) {
            int r = l ^ (1 << i);
            pq.push({v[l] + v[r], l, r});
        }
    }

    vector<int> ls, rs;
    vector<pair<int, int>> edges;
    int cnt = 1 + (2 * n - 1) * (k - 1);
    for (cnt = min(int(pq.size()), cnt); cnt--;) {
        auto [_, l, r] = pq.top();
        pq.pop();
        edges.emplace_back(l, r);
        ls.push_back(l);
        rs.push_back(r);
    }

    sort(ls.begin(), ls.end());
    ls.erase(unique(ls.begin(), ls.end()), ls.end());
    sort(rs.begin(), rs.end());
    rs.erase(unique(rs.begin(), rs.end()), rs.end());

    int n1 = ls.size(), n2 = rs.size();
    vector<vector<int>> adj(n1);
    for (auto [l, r] : edges) {
        l = lower_bound(ls.begin(), ls.end(), l) - ls.begin();
        r = lower_bound(rs.begin(), rs.end(), r) - rs.begin();
        adj[l].push_back(r);
    }

    vector<int> ord(n1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return v[ls[a]] > v[ls[b]];
    });

    vector<int> ml(n1, -1), mr(n2, -1);
    auto aug = [&]() {
        vector<int> mxl(n2, -1);
        vector<int> p(n2, -1);
        auto dfs = [&](auto &&dfs, int l, int val) -> void {
            for (auto r : adj[l]) if (!~mxl[r]) {
                mxl[r] = val;
                p[r] = l;
                if (~mr[r]) dfs(dfs, mr[r], val);
            }
        };

        for (auto l : ord) if (!~ml[l]) dfs(dfs, l, v[ls[l]]);
        int mx = -1;
        int best = -1;
        for (int r = 0; r < n2; r++) if (!~mr[r]) {
            int x = v[rs[r]] + mxl[r];
            if (mx < x) {
                mx = x;
                best = r;
            }
        }

        int r = best;
        while (~r) {
            int l = p[r];
            int prvr = ml[l];
            mr[r] = l;
            ml[l] = r;
            r = prvr;
        }
        return mx;
    };

    int ans = 0;
    k = min(k, 1 << n - 1);
    for (int _ = k; _--;) ans += aug();
    cout << ans;

    return 0;
}
