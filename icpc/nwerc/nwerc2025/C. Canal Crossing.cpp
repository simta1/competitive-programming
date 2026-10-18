#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> sub(n + 1);
    int m;
    for (cin >> m; m--;) {
        int a, b;
        cin >> a >> b;
        sub[a] ^= 1;
        sub[b] ^= 1;
    }

    ll ans = 0;
    auto dfs = [&](auto &&dfs, int cur, int par) -> void {
        for (auto [nxt, w] : adj[cur]) if (nxt != par) {
            dfs(dfs, nxt, cur);
            if (sub[nxt] & 1) {
                sub[cur] ^= 1;
                ans += w;
            }
        }
    };

    dfs(dfs, 1, -1);
    cout << ans;

    return 0;
}
