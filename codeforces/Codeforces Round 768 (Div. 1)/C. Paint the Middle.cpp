#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T, T (*op)(T, T), T (*e)()>
struct Seg {
    int sz;
    vector<T> tree;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, e());
        // for (int i = 0; i < n; i++) tree[sz | i] = v[i];
        // for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
    }
    void update(int i, T val) { // 0-based
        tree[i |= sz] = val;
        while (i >>= 1) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    T query(int l, int r) { // 0-based
        if (l > r) return e();
        T resL = e(), resR = e();
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) resL = op(resL, tree[l++]);
            if (~r & 1) resR = op(tree[r--], resR);
        }
        return op(resL, resR);
    }
};
int op(int a, int b) { return max(a, b); }
int e() { return -1e8; }

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> mn(n + 1, n), mx(n + 1, -1);
    for (int i = 0; i < n; i++) {
        mn[v[i]] = min(mn[v[i]], i);
        mx[v[i]] = max(mx[v[i]], i);
    }

    Seg<int, op, e> seg(n), seg2(n);
    for (int i = 0; i < n; i++) {
        int l = mn[v[i]], r = mx[v[i]];
        int val = 0;
        if (r == i && l + 1 < r) {
            val = max(val, max(0, seg.query(0, l - 1)) + r - l - 1);
            val = max(val, seg2.query(l + 1, r - 1) + r - 1);

            // if (i == 2) cout << seg.query(0, 1) << " " << val << "::\n";
            // if (i == 4) cout << max(0, seg.query(0, l - 1)) << " " << r - l - 1 << " " <<  val << "--\n";
            // if (i == 6) cout << seg.query(0, 3) << " " << val << "::\n";
            seg2.update(i, val - i);
        }
        // cout << i << " " << val << "::\n";
        seg.update(i, val);
    }

    cout << seg.tree[1];

    return 0;
}
