#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<pair<int, int>>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }

        vector<int> dp(n + 1);
        int ans = 0;
        auto dfs = [&](auto &&dfs, int cur, int par, int pidx) -> void {
            for (auto [nxt, idx] : adj[cur]) if (nxt != par) {
                if (pidx < idx) dp[nxt] = dp[cur];
                else dp[nxt] = dp[cur] + 1;
                ans = max(ans, dp[nxt]);
                dfs(dfs, nxt, cur, idx);
            }
        };
        dfs(dfs, 1, -1, 0);

        cout << ans + 1 << "\n";
    }

    return 0;
}
