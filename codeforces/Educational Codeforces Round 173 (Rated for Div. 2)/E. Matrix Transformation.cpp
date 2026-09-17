#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<int, vector<int> > getSCC(int n, const vector<vector<int> > &adj) {
    vector<int> dfsn(n), sccn(n, -1);
    vector<int> s(n);
    int top = 0, dfsi = 0, scci = 0;
    function<int(int)> dfs = [&](int cur) {
        int low = dfsn[cur] = ++dfsi;
        s[top++] = cur;
        for (auto nxt : adj[cur]) if (!~sccn[nxt]) low = min(low, dfsn[nxt] ? dfsn[nxt] : dfs(nxt));
        if (low == dfsn[cur]) {
            do { sccn[s[--top]] = scci; } while (s[top] != cur);
            ++scci;
        }
        return low;
    };
    for (int i = 0; i < n; i++) if (!dfsn[i]) dfs(i);
    for (int i = 0; i < n; i++) sccn[i] = scci - 1 - sccn[i];
    return {scci, sccn}; // 0-based // scci = scc 개수
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector a(n, vector<int>(m));
        vector b(n, vector<int>(m));
        for (auto &r : a) for (auto &e : r) cin >> e;
        for (auto &r : b) for (auto &e : r) cin >> e;

        auto check = [&](int bit) -> bool {
            // for (int i = 0; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         cout << (a[i][j] >> bit & 1) << " ";
            //     }
            //     cout << "\n";
            // }
            // for (int i = 0; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         cout << (b[i][j] >> bit & 1) << " ";
            //     }
            //     cout << "\n";
            // }

            vector<vector<int>> adj(n + m);

            vector<bool> r(n), c(m);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if ((a[i][j] ^ b[i][j]) >> bit & 1) {
                        if (a[i][j] >> bit & 1) r[i] = 1;
                        else c[j] = 1;
                    }

                    if (b[i][j] >> bit & 1) {
                        adj[i].push_back(n + j);
                        // cout << i << " " << n + j << "::\n";
                    }
                    else {
                        adj[n + j].push_back(i);
                        // cout << n + j << " " << i << "::\n";
                    }
                }
            }

            auto [scci, sccn] = getSCC(n + m, adj);
            vector<vector<int> > sccs(scci);
            for (int i = 0; i < n + m; i++) sccs[sccn[i]].push_back(i);

            vector<bool> dp(scci);
            for (int i = scci - 1; i >= 0; i--) {
                bool res = (sccs[i].size() == 1);
                for (auto u : sccs[i]) {
                    for (auto v : adj[u]) if (sccn[v] != sccn[u]) {
                        if (!dp[sccn[v]]) res = 0;
                    }
                }
                dp[i] = res;
            }

            for (int i = 0; i < n; i++) if (r[i]) {
                if (!dp[sccn[i]]) return false;
            }
            for (int j = 0; j < m; j++) if (c[j]) {
                if (!dp[sccn[n + j]]) return false;
            }
            return true;
        };

        if ([&]() {
            for (int bit = 0; bit < 30; bit++) if (!check(bit)) return false;
            return true;
        }()) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
