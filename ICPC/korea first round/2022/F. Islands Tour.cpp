#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int m, n;
    cin >> m >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }

    vector<int> adj(n, -1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u] = v;
    }

    vector<int> path, state(n), dp(n);
    auto dfs = [&](auto &&dfs, int cur) -> void {
        state[cur] = 1;
        path.push_back(cur);
        int nxt = adj[cur];
        if (~nxt) {
            if (!state[nxt]) dfs(dfs, nxt);
            else if (state[nxt] == 1) {
                vector<int> cycle;
                for (int i = path.size() - 1; i >= 0; i--) {
                    cycle.push_back(path[i]);
                    if (path[i] == nxt) break;
                }
                for (auto e : cycle) dp[e] = cycle.size();
            }
        }
        path.pop_back();
        state[cur] = 2;
    };
    for (int i = 0; i < n; i++) if (!state[i]) dfs(dfs, i);

    auto gdp = [&](auto &&gdp, int cur) -> void {
        int nxt = adj[cur];
        if (~nxt) {
            if (!dp[nxt]) gdp(gdp, nxt);
            dp[cur] = dp[nxt] + 1;
        }
        else dp[cur] = 1;
    };
    for (int i = 0; i < n; i++) if (!dp[i]) gdp(gdp, i);

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
