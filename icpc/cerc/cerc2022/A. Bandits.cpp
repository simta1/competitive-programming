#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<pair<int, int>> edges(n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
        edges[i] = {u, v};
    }

    vector<int> dep(n + 1), pos(n + 1), euler(2 * n - 1);
    vector<ll> dist(n + 1);
    int ei = 0;
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        euler[pos[cur] = ei++] = cur;
        for (auto [nxt, cost] : adj[cur]) if (nxt != par) {
            dep[nxt] = dep[cur] + 1;
            dist[nxt] = dist[cur] + cost;
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
        auto [l, r] = minmax(pos[a], pos[b]);
        int i = __lg(r - l + 1);
        int u = ac[i][l];
        int v = ac[i][r - (1 << i) + 1];
        return dep[u] < dep[v] ? u : v;
    };
    auto get_dist = [&](int a, int b) {
        return dist[a] + dist[b] - 2 * dist[get_lca(a, b)];
    };

    vector<int> sz(n + 1);
    vector<bool> rm(n + 1);
    auto get_sz = [&](auto &&get_sz, int cur, int par) -> int {
        sz[cur] = 1;
        for (auto [nxt, _] : adj[cur]) if (nxt != par && !rm[nxt]) {
            sz[cur] += get_sz(get_sz, nxt, cur);
        }
        return sz[cur];
    };
    auto get_ct = [&](auto &&get_ct, int cur, int par, int tot) -> int {
        for (auto [nxt, _] : adj[cur]) if (nxt != par && !rm[nxt]) {
            if (sz[nxt] * 2 > tot) return get_ct(get_ct, nxt, cur, tot);
        }
        return cur;
    };

    vector<int> cpar(n + 1, -1), cdep(n + 1);
    auto build = [&](auto &&build, int cur, int par) -> void {
        int tot = get_sz(get_sz, cur, -1);
        int ct = get_ct(get_ct, cur, -1, tot);
        if (~par) {
            cpar[ct] = par;
            cdep[ct] = cdep[par] + 1;
        }
        rm[ct] = 1;
        for (auto [nxt, _] : adj[ct]) if (!rm[nxt]) {
            build(build, nxt, ct);
        }
    };
    build(build, 1, -1);

    vector<ordered_set<pair<ll, int>>> s(n + 1), s_prv(n + 1);
    auto upd = [&](int x, int r) {
        static int id = 0;
        for (int prv = -1, cur = x; ~cur; prv = cur, cur = cpar[cur]) {
            ll val = r - get_dist(cur, x);
            s[cur].insert({val, ++id});
            if (~prv) s_prv[prv].insert({val, id});
        }
    };
    auto qry = [&](int u, int v) {
        int res = 0;
        if (cdep[u] > cdep[v]) swap(u, v);
        for (int prv = -1, cur = v; ~cur; prv = cur, cur = cpar[cur]) {
            ll val = max(get_dist(cur, v), get_dist(cur, u));
            res += s[cur].size() - s[cur].order_of_key({val, -1});
            if (~prv) res -= s_prv[prv].size() - s_prv[prv].order_of_key({val, -1});
        }
        return res;
    };

    int q;
    for (cin >> q; q--;) {
        char op;
        cin >> op;
        if (op == '+') {
            int x, r;
            cin >> x >> r;
            upd(x, r);
        }
        else {
            int x;
            cin >> x;
            auto [a, b] = edges[x];
            cout << qry(a, b) << "\n";
        }
    }
    return 0;
}
