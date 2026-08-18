#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        while (m--) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<pair<int, int>> ans;
        if ([&]() {
            for (int u = 1; u <= n; u++) if (adj[u].size() >= 4) {
                vector<int> p(n + 1);
                p[u] = u;

                vector<bool> connected(n + 1);
                for (auto v : adj[u]) connected[v] = 1;

                auto dfs = [&](auto &&dfs, int cur) {
                    if (connected[cur]) return cur;
                    for (auto nxt : adj[cur]) if (!p[nxt]) {
                        p[nxt] = cur;
                        int x = dfs(dfs, nxt);
                        if (x) return x;
                    }
                    return 0;
                };
                for (auto v : adj[u]) {
                    connected[v] = 0;
                    p[v] = u;
                    int v2 = dfs(dfs, v);
                    if (v2) {
                        for (int cur = v2; cur != v; cur = p[cur]) ans.emplace_back(cur, p[cur]);
                        ans.emplace_back(u, v);
                        ans.emplace_back(u, v2);

                        int cnt = 0;
                        for (auto x : adj[u]) if (x != v && x != v2) {
                            ans.emplace_back(u, x);
                            if (++cnt == 2) break;
                        }
                        return true;
                    }
                    connected[v] = 0;
                }
            }
            return false;
        }()) {
            cout << "YES\n";
            cout << ans.size() << "\n";
            for (auto [a, b] : ans) cout << a << " " << b << "\n";
        }
        else cout << "NO\n";

        
    }

    return 0;
}
