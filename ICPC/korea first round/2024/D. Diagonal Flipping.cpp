#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> p, sz;
    int n;
    DSU(int n) : p(2 * n), sz(2 * n), n(n) {
        iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.begin() + n, 1);
    }
    int find(int a) {
        return p[a] == a ? a : p[a] = find(p[a]);
    }
    void _merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        p[a] = b;
        sz[b] += sz[a];
    }
    void merge(int a, int b, bool isOpp) {
        if (isOpp) {
            _merge(a, b + n);
            _merge(a + n, b);
        }
        else {
            _merge(a, b);
            _merge(a + n, b + n);
        }
    }
    int query(int a, int b) { // 0: 같은 집합, 1: 반대쪽 집합, -1: 관계 모름
        return find(a) == find(b) ? 0 : find(a) == find(b + n) ? 1 : -1;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector v(n, vector<int>(m));
    for (auto &r : v) for (auto &e : r) cin >> e;

    if (n == 1 || m == 1) {
        int ans = 0;
        for (auto &r : v) for (auto &e : r) ans += e;
        cout << ans;
        return 0;
    }

    auto f = [&](int i, int j) { // "\"
        return i + j;
    };
    auto g = [&](int i, int j) { // "/"
        return n + m - 1 + i - j + m - 1;
    };

    DSU dsu(n + m - 1 << 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int a = f(i, j), b = g(i, j);
            int x = dsu.query(a, b);
            if (~x && x != v[i][j]) {
                cout << "-1";
                return 0;
            }
            dsu.merge(f(i, j), g(i, j), v[i][j]);
        }
    }

    int ans = 0;
    for (auto [i, j] : vector<pair<int, int>>{{0, 0}, {0, 1}}) {
        int x = f(i, j);
        int a = dsu.find(x);
        int b = dsu.find(x + dsu.n);
        ans += min(dsu.sz[a], dsu.sz[b]);
    }
    cout << ans;

    return 0;
}
