#include <bits/stdc++.h>
using namespace std;
using ll = long long;

auto bimatch(int n1, int n2, const vector<vector<int>> &adj) { // O(VE) // 0-based
    vector<int> ml(n1, -1), mr(n2, -1), vr(n2);
    int t = 1;
    auto dfs = [&](auto &&dfs, int l) -> bool {
        for (auto r : adj[l]) if (vr[r] != t) {
            vr[r] = t;
            if (!~mr[r] || dfs(dfs, mr[r])) {
                ml[l] = r;
                mr[r] = l;
                return true;
            }
        }
        return false;
    };
    int res = 0;
    for (int l = 0; l < n1; ++l, ++t) res += dfs(dfs, l);
    return tuple{res, ml, mr};
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, c;
        cin >> n >> c;

        string a, b;
        cin >> a >> b;

        int s = 0;
        for (int i = 0; i < n; i++) s |= (a[i] != b[i]) << i;

        vector<bool> rm(1 << n);
        while (c--) {
            string st;
            cin >> st;

            int mask = 0;
            for (int i = 0; i < n; i++) mask |= (st[i] == '.') << i;
            rm[mask] = 1;
        }

        vector<vector<int>> adj(1 << n), adj2(1 << n);
        for (int u = 0; u < (1 << n); u++) if (__builtin_popcount(u) & 1) {
            for (int i = 0; i < n; i++) {
                int v = u ^ (1 << i);
                if (rm[u] || rm[v]) continue;
                adj[u].push_back(v);
                if (u != s && v != s) adj2[u].push_back(v);
            }
        }

        auto b1 = bimatch(1 << n, 1 << n, adj);
        auto b2 = bimatch(1 << n, 1 << n, adj2);
        if (get<0>(b1) != get<0>(b2)) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
