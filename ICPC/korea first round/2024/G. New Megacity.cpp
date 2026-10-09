#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        return a == p[a] ? a : p[a] = find(p[a]);
    }
    void merge(int a, int b) {
        p[find(a)] = find(b);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<array<int, 4>> edges(m);
    for (int i = 0; i < m; i++) {
        auto &[w, u, v, idx] = edges[i];
        cin >> u >> v >> w;
        idx = i;
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n + 1);

    vector<int> dfsn(n + 1);
    vector<vector<pair<int, int>>> adj(n + 1);

    vector<int> ans(m);
    for (int i = 0, j = 0; i < m; i = j) {
        while (j < m && edges[i][0] == edges[j][0]) ++j;

        vector<int> V;
        for (int k = i; k < j; k++) {
            auto [w, u, v, idx] = edges[k];
            u = dsu.find(u);
            v = dsu.find(v);
            if (u == v) ans[idx] = 3;
            else {
                V.push_back(u);
                V.push_back(v);
                adj[u].emplace_back(v, idx);
                adj[v].emplace_back(u, idx);
            }
        }

        int dfsi = 0;
        auto dfs = [&](auto &&dfs, int cur, int pid) -> int {
            int low = dfsn[cur] = ++dfsi;
            for (auto [nxt, id] : adj[cur]) if (id != pid) {
                if (!dfsn[nxt]) {
                    int nlow = dfs(dfs, nxt, id);
                    low = min(low, nlow);
                    if (nlow > dfsn[cur]) ans[id] = 1;
                }
                else low = min(low, dfsn[nxt]);
            }
            return low;
        };
        for (auto v : V) if (!dfsn[v]) dfs(dfs, v, -1);
        for (auto v : V) {
            adj[v].clear();
            dfsn[v] = 0;
        }

        for (int k = i; k < j; k++) {
            auto [w, u, v, idx] = edges[k];
            if (!ans[idx]) ans[idx] = 2;
            dsu.merge(u, v);
        }

    }

    for (auto e : ans) cout << e << "\n";

    return 0;
}
