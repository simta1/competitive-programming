#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<pair<int, int>> edges(n - 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i - 1] = {u, v};
    }

    vector<vector<int> > chd(n + 1);
    vector<int> sz2(n + 1, 1), dep(n + 1), p(n + 1), in(n + 1), top(n + 1);
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        for (auto nxt : adj[cur]) if (nxt != par) {
            p[nxt] = cur;
            dep[nxt] = dep[cur] + 1;
            mkt(mkt, nxt, cur);
            chd[cur].push_back(nxt);
            sz2[cur] += sz2[nxt];
            if (sz2[chd[cur][0]] < sz2[nxt]) swap(chd[cur][0], chd[cur].back());
        }
    };
    mkt(mkt, 1, -1);
    int dfsi = 0;
    auto ett = [&](auto &&ett, int cur) -> void {
        in[cur] = ++dfsi;
        for (auto nxt : chd[cur]) {
            top[nxt] = (nxt == chd[cur][0] ? top[cur] : nxt);
            ett(ett, nxt);
        }
    };
    top[1] = 1;
    ett(ett, 1);

    map<int, vector<int>> mp;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        mp[a].push_back(i);
    }

    int sz = 1;
    while (sz < n + 1) sz <<= 1;
    vector<int> tree(sz << 1), lazy(sz << 1);
    auto propagate = [&](int node, int s, int e) {
        if (lazy[node]) {
            tree[node] = max(tree[node], lazy[node]);
            if (s != e) {
                lazy[node << 1] = max(lazy[node << 1], lazy[node]);
                lazy[node << 1 | 1] = max(lazy[node << 1 | 1], lazy[node]);
            }
            lazy[node] = 0;
        }
    };
    auto update = [&](auto &&update, int node, int s, int e, int l, int r, ll val) {
        propagate(node, s, e);
        if (l <= s && e <= r) {
            lazy[node] = val;
            propagate(node, s, e);
            return;
        }
        if (l > e || s > r) return;
        int m = s + e >> 1;
        update(update, node << 1, s, m, l, r, val);
        update(update, node << 1 | 1, m + 1, e, l, r, val);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    };

    auto hupdate = [&](int a, int b, int x) { // O(log^2N)
        vector<pair<int, int>> res;
        while (top[a] != top[b]) {
            if (dep[top[a]] > dep[top[b]]) swap(a, b);
            res.emplace_back(in[top[b]], in[b]);
            b = p[top[b]];
        }
        if (dep[a] > dep[b]) swap(a, b);
        // res += seg.query(in[a], in[b]); // 정점쿼리
        // if (in[a] + 1 <= in[b]) res += seg.query(in[a] + 1, in[b]); // 간선쿼리
        if (in[a] + 1 <= in[b]) res.emplace_back(in[a] + 1, in[b]);

        sort(res.begin(), res.end());
        int p = 1;
        for (auto [l, r] : res) {
            if (p <= l - 1) update(update, 1, 0, sz - 1, p, l - 1, x);
            p = r + 1;
        }
        if (p <= n) update(update, 1, 0, sz - 1, p, n, x);
    };

    int mx = 0;
    for (auto [x, nodes] : mp) {
        int cnt = nodes.size();
        if (cnt == 1) continue;
        else if (cnt == 2) {
            int a = nodes[0], b = nodes[1];
            hupdate(a, b, x);
        }
        else mx = max(mx, x);
    }

    auto build = [&](auto &&build, int node, int s, int e) -> void {
        propagate(node, s, e);
        if (s != e) {
            int m = s + e >> 1;
            build(build, node << 1, s, m);
            build(build, node << 1 | 1, m + 1, e);
        }
    };
    build(build, 1, 0, sz - 1);

    for (auto [u, v] : edges) {
        if (p[u] == v) swap(u, v);
        cout << max(mx, tree[in[v] | sz]) << "\n";
    }

    return 0;
}
