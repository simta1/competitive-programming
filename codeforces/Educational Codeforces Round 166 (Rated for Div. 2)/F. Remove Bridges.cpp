#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> h(n + 1, 1), p(n + 1, -1);
        auto mkt = [&](auto &&mkt, int cur, int par) -> void {
            for (auto nxt : adj[cur]) if (nxt != par) {
                p[nxt] = cur;
                mkt(mkt, nxt, cur);
                h[cur] = max(h[cur], h[nxt] + 1);
            }
        };
        mkt(mkt, 1, -1);

        vector<int> heavy(n + 1, -1);
        for (int i = 1; i <= n; i++) {
            for (auto j : adj[i]) if (j != p[i]) {
                if (!~heavy[i] || h[heavy[i]] < h[j]) heavy[i] = j;
            }
        }

        vector<int> d;
        for (int i = 1; i <= n; i++) {
            if (i == 1 || heavy[p[i]] != i) d.push_back(h[i]);
        }
        sort(d.rbegin(), d.rend());
        // for (auto &e : d) cout << e << " "; cout << "\n";

        for (int i = 1; i < d.size(); i++) d[i] += d[i - 1];
        d.resize(2 * n, n);

        for (int k = 1; k < n; k++) cout << n - d[2 * k - 2] << " ";
        cout << "\n";
    }

    return 0;
}
