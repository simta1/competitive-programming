#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int s = -1;
    int mn = 1e8;
    for (int i = 1; i <= n; i++) if (adj[i].size() != 1) {
        int cnt = 0;
        for (auto j : adj[i]) if (adj[j].size() != 1) ++cnt;
        if (mn > cnt) {
            mn = cnt;
            s = i;
        }
    }

    vector<int> ans(n + 1);
    int lo = 1, hi = n;
    auto dfs = [&](auto &&dfs, int cur, bool dir) -> void {
        ans[cur] = dir ? hi-- : lo++;
        int go = -1;
        for (auto nxt : adj[cur]) if (!ans[nxt]) {
            if (adj[nxt].size() == 1) ans[nxt] = dir ? lo++ : hi--;
            else go = nxt;
        }
        if (~go) dfs(dfs, go, !dir);
    };
    dfs(dfs, s, 0);

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";

    return 0;
}
