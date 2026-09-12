#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T, T (*op)(T&, T&), T (*e)()>
struct Seg {
    int sz;
    vector<T> tree;
    Seg(int n, const vector<int> &v) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, e());
        for (int i = 0; i < n; i++) tree[sz | i] = T(v[i]);
        for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]); 
        // cout << tree[1].val << "--\n";
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

struct Node {
    bool e = true;
    ll mn, mx, val;
    Node() = default;
    Node(ll mn, ll mx, ll val) : e(0), mn(mn), mx(mx), val(val) {}
    Node(ll x) {
        e = 0;
        mn = mx = x;
        val = 0;
    }
};

Node e() {
    return Node();
}

Node op(Node &l, Node &r) {
    if (l.e) return r;
    if (r.e) return l;
    return Node(min(l.mn, r.mn),
                max(l.mx, r.mx),
                max({l.val, r.val, r.mx - l.mn}));
}

Node op2(Node &l, Node &r) {
    if (l.e) return r;
    if (r.e) return l;
    return Node(min(l.mn, r.mn),
                max(l.mx, r.mx),
                max({l.val, r.val, l.mx - r.mn}));
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, q;
        cin >> n >> q;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = v[i] - i;
            b[i] = v[i] + i;
        }

        Seg<Node, op, e> aseg(n, a);
        Seg<Node, op2, e> bseg(n, b);

        // for (auto &e : a) cout << e << " "; cout << "\n";
        // cout << aseg.query(0, n - 1).val << "::\n";
        // cout << bseg.query(0, n - 1).val << "::\n";
        cout << max(aseg.query(0, n - 1).val, bseg.query(0, n - 1).val) << "\n";

        while (q--) {
            int idx, x;
            cin >> idx >> x;
            --idx;
            aseg.update(idx, x - idx);
            bseg.update(idx, x + idx);
            cout << max(aseg.query(0, n - 1).val, bseg.query(0, n - 1).val) << "\n";
        }
    }

    return 0;
}
