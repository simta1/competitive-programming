#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using mat = array<array<ll, 5>, 5>;
constexpr ll INF = 1e18;
mat f(ll a, ll b) {
    mat res{};
    for (auto &r : res) r.fill(-INF);
    res[0][1] = res[1][2] = res[2][3] = res[3][4] = a + b;
    res[0][2] = res[2][4] = a + 2 * b;
    res[1][1] = res[3][3] = a;
    res[0][0] = res[2][2] = res[4][4] = 0;
    return res;
}

mat op(const mat &a, const mat &b) {
    mat res{};
    for (auto &r : res) r.fill(-INF);
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

mat e() {
    mat res{};
    for (auto &r : res) r.fill(-INF);
    for (int i = 0; i < 5; i++) res[i][i] = 0;
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (auto &e : a) cin >> e;
    for (auto &e : b) cin >> e;

    int sz = 1;
    while (sz < n) sz <<= 1;
    vector<mat> tree(sz << 1);
    for (int i = 0; i < n; i++) tree[i | sz] = f(a[i], b[i]);
    for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);

    auto update = [&](int i) {
        tree[i |= sz] = f(a[i], b[i]);
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    };
    auto query = [&](int l, int r) { // 0-based
        mat resL = e(), resR = e();
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) resL = op(resL, tree[l++]);
            if (~r & 1) resR = op(tree[r--], resR);
        }
        return op(resL, resR);
    };

    int q;
    for (cin >> q; q--;) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            a[l - 1] = r;
            update(l - 1);
        }
        else if (op == 2) {
            b[l - 1] = r;
            update(l - 1);
        }
        else {
            cout << query(l - 1, r - 1)[0][4] << "\n";
        }
    }

    return 0;
}
