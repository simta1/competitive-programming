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

struct BIT {
    vector<int> tree;
    BIT(int n) : tree(n + 1) {}
    void update(int i, int add) {
        for (; i < tree.size(); i += i & -i) tree[i] += add;
    }
    int query(int l, int r) {
        int res = 0;
        for (int i = r; i > 0; i -= i & -i) res += tree[i];
        for (int i = l - 1; i > 0; i -= i & -i) res -= tree[i];
        return res;
    }
};

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

    DSU dsu_mn(n + 1), dsu_mx(n + 1);
    vector<vector<int>> chd_mn(n + 1), chd_mx(n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto j : adj[i]) if (j <= i) {
            // cout << i << " -> " << dsu_mx.find(j) << "\n";
            chd_mx[i].push_back(dsu_mx.find(j));
            dsu_mx.merge(j, i);
        }
    }
    for (int i = n; i >= 1; i--) {
        for (auto j : adj[i]) if (j >= i) {
            chd_mn[i].push_back(dsu_mn.find(j));
            dsu_mn.merge(j, i);
        }
    }

    auto bfs = [&](int root, const vector<vector<int>> &chd, vector<int> &dep) {
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto nxt : chd[cur]) {
                dep[nxt] = dep[cur] + 1;
                q.push(nxt);
            }
        }
    };
    vector<int> dep_mn(n + 1), dep_mx(n + 1);
    bfs(n, chd_mx, dep_mx);
    bfs(1, chd_mn, dep_mn);
    // for (int i = 1; i <= n; i++) cout << dep_mx[i] << " "; cout << "\n";

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += dep_mn[i];
        ans += dep_mx[i];
    }
    // cout << ans << "\n";

    vector<int> in(n + 1), out(n + 1);
    int dfsi = 0;
    auto ett = [&](auto &ett, int cur) -> void {
        in[cur] = ++dfsi;
        for (auto nxt : chd_mx[cur]) ett(ett, nxt);
        out[cur] = dfsi;
    };
    ett(ett, n);

    BIT fw(n);
    auto dfs = [&](auto &&dfs, int cur) -> void {
        ans -= 2 * fw.query(in[cur], out[cur]);
        fw.update(in[cur], 1);
        for (auto nxt : chd_mn[cur]) {
            dfs(dfs, nxt);
        }
        fw.update(in[cur], -1);
    };
    dfs(dfs, 1);

    cout << ans << "\n";

    int q;
    cin >> q;

    chd_mn.resize(n + q + 1);
    dep_mn.resize(n + q + 1);
    while (q--) {
        int k;
        cin >> k;
        int cur = n + 1;
        chd_mn[k].push_back(cur);
        dep_mn[cur] = dep_mn[k] + 1;
        ans += n - dep_mn[cur];
        ++n;
        cout << ans << "\n";
    }

    return 0;
}
