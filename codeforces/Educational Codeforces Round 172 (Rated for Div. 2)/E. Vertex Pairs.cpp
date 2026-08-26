#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int N = 2 * n;
    vector<int> v(N + 1);
    vector<pair<int, int>> node(n + 1);
    for (int i = 1; i <= N; i++) {
        cin >> v[i];
        if (!node[v[i]].first) node[v[i]].first = i;
        else node[v[i]].second = i;
    }

    auto other = [&](int x) {
        auto [a, b] = node[v[x]];
        return a ^ b ^ x;
    };

    vector<vector<int>> adj(N + 1);
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto f = [&](int root) {
        vector<int> euler(2 * N - 1), in(N + 1), dep(N + 1), p(N + 1, -1);
        int sz = 0;
        auto mkt = [&](auto &&mkt, int cur, int par) -> void {
            euler[in[cur] = sz++] = cur;
            for (auto nxt : adj[cur]) if (nxt != par) {
                p[nxt] = cur;
                dep[nxt] = dep[cur] + 1;
                mkt(mkt, nxt, cur);
                euler[sz++] = cur;
            }
        };
        mkt(mkt, root, -1);

        vector<vector<int>> ac(__lg(sz) + 1, euler);
        for (int i = 1; i <= __lg(sz); i++) {
            for (int j = 0; j + (1 << i) - 1 < sz; j++) {
                int u = ac[i - 1][j];
                int v = ac[i - 1][j + (1 << i - 1)];
                ac[i][j] = dep[u] < dep[v] ? u : v;
            }
        }

        auto getLCA = [&](int a, int b) {
            auto [l, r] = minmax(in[a], in[b]);
            int i = __lg(r - l + 1);
            int u = ac[i][l];
            int v = ac[i][r - (1 << i) + 1];
            return dep[u] < dep[v] ? u : v;
        };

        vector<int> use(N + 1, -1);
        use[root] = 1;

        auto mark = [&](int v) {
            for (; v != root && !~use[v]; v = p[v]) use[v] = 1;
        };

        for (int i = 1; i <= n; i++) {
            auto [a, b] = node[i];
            int lca = getLCA(a, b);
            mark(lca);
        }

        for (int i = N; i >= 1; i--) {
            if (!~use[i]) {
                queue<int> q;
                q.push(i);
                while (!q.empty()) {
                    auto cur = q.front();
                    q.pop();
                    use[cur] = 0;
                    mark(other(cur));
                    for (auto nxt : adj[cur]) if (nxt != p[cur]) {
                        if (!~use[nxt]) {
                            q.push(nxt);
                        }
                    }
                }
            }
        }

        vector<int> res;
        for (int i = N; i >= 1; i--) if (use[i]) res.push_back(i);
        return res;
    };

    auto ans = min(f(node[1].first), f(node[1].second));
    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (auto &e : ans) cout << e << " ";

    return 0;
}
