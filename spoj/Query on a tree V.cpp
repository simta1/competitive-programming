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

    vector<int> euler(2 * n - 1), dep(n + 1), pos(n + 1);
    int ei = 0;
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        euler[pos[cur] = ei++] = cur;
        for (auto nxt : adj[cur]) if (nxt != par) {
            dep[nxt] = dep[cur] + 1;
            mkt(mkt, nxt, cur);
            euler[ei++] = cur;
        }
    };
    mkt(mkt, 1, -1);
    vector<vector<int>> ac(__lg(ei) + 1, euler);
    for (int i = 1; i <= __lg(ei); i++) {
        for (int j = 0; j + (1 << i) - 1 < ei; j++) {
            int u = ac[i - 1][j];
            int v = ac[i - 1][j + (1 << i - 1)];
            ac[i][j] = dep[u] < dep[v] ? u : v;
        }
    }
    auto get_lca = [&](int a, int b) {
        int l = pos[a], r = pos[b];
        if (l > r) swap(l, r);
        int i = __lg(r - l + 1);
        int u = ac[i][l];
        int v = ac[i][r - (1 << i) + 1];
        return dep[u] < dep[v] ? u : v;
    };
    auto get_dist = [&](int a, int b) {
        int lca = get_lca(a, b);
        return dep[a] + dep[b] - 2 * dep[lca];
    };

    vector<int> sz(n + 1);
    vector<bool> rm(n + 1);
    auto get_sz = [&](auto &&get_sz, int cur, int par) -> int {
        sz[cur] = 1;
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            sz[cur] += get_sz(get_sz, nxt, cur);
        }
        return sz[cur];
    };
    auto get_ct = [&](auto &&get_ct, int cur, int par, int tot) -> int {
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            if (sz[nxt] * 2 > tot) return get_ct(get_ct, nxt, cur, tot);
        }
        return cur;
    };
    vector<int> cpar(n + 1, -1);
    auto build = [&](auto &&build, int cur, int par) -> void {
        int tot = get_sz(get_sz, cur, -1);
        int ct = get_ct(get_ct, cur, -1, tot);
        cpar[ct] = par;
        rm[ct] = 1;
        for (auto nxt : adj[ct]) if (!rm[nxt]) {
            build(build, nxt, ct);
        }
    };
    build(build, 1, -1);

    constexpr int INF = 1e8;
    vector<multiset<int>> s(n + 1);
    auto upd = [&](int x, bool add) {
        if (add) {
            for (int cur = x; ~cur; cur = cpar[cur]) {
                s[cur].insert(get_dist(cur, x));
            }
        }
        else {
            for (int cur = x; ~cur; cur = cpar[cur]) {
                s[cur].erase(s[cur].find(get_dist(cur, x)));
            }
        }
    };
    auto qry = [&](int x) {
        int res = INF;
        for (int cur = x; ~cur; cur = cpar[cur]) if (!s[cur].empty()) {
            res = min(res, *s[cur].begin() + get_dist(cur, x));
        }
        return res;
    };

    vector<bool> white(n + 1);
    int q;
    for (cin >> q; q--;) {
        int op, x;
        cin >> op >> x;

        if (op == 0) {
            white[x] = !white[x];
            upd(x, white[x]);
        }
        else {
            int ans = qry(x);
            cout << (ans == INF ? -1 : ans) << "\n";
        }
    }

    return 0;
}
