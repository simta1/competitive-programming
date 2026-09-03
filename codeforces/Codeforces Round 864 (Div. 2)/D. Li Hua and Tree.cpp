#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<ll> dp(n + 1);
    for (int i = 1; i <= n; i++) cin >> dp[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n + 1, 1), p(n + 1, -1);
    vector<set<pair<int, int>>> chd(n + 1);
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        for (auto nxt : adj[cur]) if (nxt != par) {
            p[nxt] = cur;
            mkt(mkt, nxt, cur);
            sz[cur] += sz[nxt];
            dp[cur] += dp[nxt];
            chd[cur].emplace(sz[nxt], -nxt);
        }
    };
    mkt(mkt, 1, -1);

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            cout << dp[x] << "\n";
        }
        else {
            if (chd[x].empty()) continue;
            int son = -chd[x].rbegin()->second;
            int fa = p[x];
            chd[fa].erase({sz[x], -x});
            chd[x].erase({sz[son], -son});
            dp[x] -= dp[son];
            sz[x] -= sz[son];
            dp[son] += dp[x];
            sz[son] += sz[x];
            chd[fa].emplace(sz[son], -son);
            chd[son].emplace(sz[x], -x);
            p[x] = son;
            p[son] = fa;
        }
    }

    return 0;
}
