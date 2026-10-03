#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto get_scc(int n, const vector<vector<int>> &adj) { // adj는 1-based // O(V+E)
    vector<int> dfsn(n + 1), sccn(n + 1, -1);
    vector<int> s(n);
    int top = 0, dfsi = 0, scci = 0;
    auto dfs = [&](auto &&dfs, int cur) -> int {
        int low = dfsn[cur] = ++dfsi;
        s[top++] = cur;
        for (auto nxt : adj[cur]) if (!~sccn[nxt]) low = min(low, dfsn[nxt] ? dfsn[nxt] : dfs(dfs, nxt));
        if (low == dfsn[cur]) {
            do { sccn[s[--top]] = scci; } while (s[top] != cur);
            ++scci;
        }
        return low;
    };
    for (int i = 1; i <= n; i++) if (!dfsn[i]) dfs(dfs, i);
    // for (int i = 1; i <= n; i++) sccn[i] = scci - 1 - sccn[i];
    return pair{scci, sccn}; // 0-based // scci = scc 개수
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges;
    vector<array<int, 3>> qs;
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        // cout << v << " " << u << " " << -t << "\n";
        adj[v].push_back(u);
        if (t) edges.emplace_back(v, u);
        qs.push_back({t, u, v});
    }

    auto [scci, sccn] = get_scc(n, adj);
    for (auto [u, v] : edges) {
        if (sccn[u] == sccn[v]) {
            cout << "No";
            return 0;
        }
    }

    // for (auto [t, u, v] : qs) {
    //     if (t) assert(sccn[u] < sccn[v]);
    //     else assert(sccn[u] <= sccn[v]);
    // }

    cout << "Yes\n";
    for (int i = 1; i <= n; i++) {
        cout << sccn[i] + 1 << " ";
    }

    return 0;
}
