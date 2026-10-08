#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    struct Node {
        int l, r;
        ull val;
        Node() { l = r = val = 0; }
    };
    vector<Node> tree;
    auto newNode = [&]() -> int {
        tree.emplace_back();
        return tree.size() - 1;
    };
    vector<int> roots(n + 1);
    roots[0] = newNode();
    auto upd = [&](auto &&upd, int old, int s, int e, int i, ull add) {
        int node = newNode();
        tree[node] = tree[old];
        if (s == e) {
            tree[node].val ^= add;
            return node;
        }
        int m = s + e >> 1;
        if (i <= m) tree[node].l = upd(upd, tree[old].l, s, m, i, add);
        else tree[node].r = upd(upd, tree[old].r, m + 1, e, i, add);
        tree[node].val = tree[tree[node].l].val ^ tree[tree[node].r].val;
        return node;
    };

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dep(n + 1), pos(n + 1), euler(2 * n - 1), p(n + 1);
    int ei = 0;
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        euler[pos[cur] = ei++] = cur;
        for (auto nxt : adj[cur]) if (nxt != par) {
            p[nxt] = cur;
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
    auto getLCA = [&](int a, int b) {
        auto [l, r] = minmax(pos[a], pos[b]);
        int i = __lg(r - l + 1);
        int u = ac[i][l];
        int v = ac[i][r - (1 << i) + 1];
        return dep[u] < dep[v] ? u : v;
    };

    mt19937_64 rng;
    vector<ull> h(n + 1);
    for (int i = 1; i <= n; i++) h[i] = rng();
    auto dfs = [&](auto &&dfs, int cur, int par) -> void {
        roots[cur] = upd(upd, roots[par], 1, n, v[cur], h[v[cur]]);
        for (auto nxt : adj[cur]) if (nxt != par) {
            dfs(dfs, nxt, cur);
        }
    };
    dfs(dfs, 1, 0);

    auto qry = [&](auto &&qry, int u, int v, int lca, int lcapar, int s, int e, int l, int r) {
        if (l > e || s > r) return -1;
        ull cur = tree[u].val ^ tree[v].val ^ tree[lca].val ^ tree[lcapar].val;
        if (l <= s && e <= r && !cur) return -1;

        if (s == e) return s;
        int m = s + e >> 1;
        int res = qry(qry, tree[u].l, tree[v].l, tree[lca].l, tree[lcapar].l, s, m, l, r);
        if (~res) return res;
        return qry(qry, tree[u].r, tree[v].r, tree[lca].r, tree[lcapar].r, m + 1, e, l, r);
    };

    while (q--) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        int lca = getLCA(u, v);
        cout << qry(qry, roots[u], roots[v], roots[lca], roots[p[lca]], 1, n, l, r) << "\n";
    }

    return 0;
}
