#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p, r;
    vector<array<int, 3>> h;
    int cnt;
    DSU(int n) : p(n), r(n), cnt(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (a != p[a]) a = p[a];
        return a;
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (r[a] > r[b]) swap(a, b);
        h.push_back({a, b, r[b]});
        p[a] = b;
        r[b] += r[a] == r[b];
        --cnt;
    }
    void rollback(int sz) {
        while (h.size() > sz) {
            auto [a, b, rb] = h.back();
            h.pop_back();
            p[a] = a;
            r[b] = rb;
            ++cnt;
        }
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    int sz = 1;
    while (sz < q) sz <<= 1;

    using Edge = array<int, 3>;
    vector<vector<Edge>> tree(sz << 1);
    auto update = [&](int l, int r, const Edge &e) {
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) tree[l++].push_back(e);
            if (~r & 1) tree[r--].push_back(e);
        }
    };

    map<array<int, 3>, int> mp;
    for (int t = 0; t < q; t++) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        --x, --y;
        if (x > y) swap(x, y);
        array<int, 3> e = {c - 'A', x, y};
        if (mp.count(e)) {
            update(mp[e], t - 1, e);
            mp.erase(e);
        }
        else mp[e] = t;
    }

    for (auto [e, t] : mp) update(t, q - 1, e);

    DSU dsu_a(n), dsu_ab(n);
    auto dfs = [&](auto &&dfs, int node, int s, int e) -> void {
        if (q - 1 < s) return;
        int tmp = dsu_a.h.size(), tmp2 = dsu_ab.h.size();
        for (auto [op, x, y] : tree[node]) {
            if (!op) dsu_a.merge(x, y);
            dsu_ab.merge(x, y);
        }

        if (s != e) {
            int m = s + e >> 1;
            dfs(dfs, node << 1, s, m);
            dfs(dfs, node << 1 | 1, m + 1, e);
        }
        else cout << dsu_a.cnt - dsu_ab.cnt << "\n";

        dsu_a.rollback(tmp);
        dsu_ab.rollback(tmp2);
    };
    dfs(dfs, 1, 0, sz - 1);

    return 0;
}
