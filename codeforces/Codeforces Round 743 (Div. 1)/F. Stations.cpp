#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg {
    int sz;
    vector<ll> tree, lazy;
    Seg() = default;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1);
        lazy.resize(sz << 1);
        for (int i = 0; i < n; i++) tree[i | sz] = 1;
        for (int i = sz - 1; i >= 1; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    void apply(int node, int s, int e, ll add) {
        tree[node] += (e - s + 1) * add;
        lazy[node] += add;
    }
    void push(int node, int s, int e) {
        if (lazy[node]) {
            int m = s + e >> 1;
            apply(node << 1, s, m, lazy[node]);
            apply(node << 1 | 1, m + 1, e, lazy[node]);
            lazy[node] = 0;
        }
    }
    void upd(int node, int s, int e, int l, int r, ll add) {
        if (l <= s && e <= r) {
            apply(node, s, e, add);
            return;
        }
        if (l > e || s > r) return;
        push(node, s, e);
        int m = s + e >> 1;
        upd(node << 1, s, m, l, r, add);
        upd(node << 1 | 1, m + 1, e, l, r, add);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }
    void upd(int l, int r, int add) { upd(1, 0, sz - 1, l, r, add); }
    ll qry(int node, int s, int e, int l, int r) {
        if (l <= s && e <= r) return tree[node];
        if (l > e || s > r) return 0;
        push(node, s, e);
        int m = s + e >> 1;
        return qry(node << 1, s, m, l, r) + qry(node << 1 | 1, m + 1, e, l, r);
    }
    ll qry(int l, int r) { return qry(1, 0, sz - 1, l, r); }
};

Seg seg;

struct SegBeats {
    static constexpr int NEG = -1e8;
    struct Node {
        int mx, mx2, mxcnt, lazy = -1;
    };
    Node op(const Node &a, const Node &b) {
        Node res = {NEG, NEG, 0, -1};
        if (a.mx == b.mx) {
            res.mx = a.mx;
            res.mxcnt = a.mxcnt + b.mxcnt;
            res.mx2 = max(a.mx2, b.mx2);
        }
        else if (a.mx < b.mx) {
            res.mx = b.mx;
            res.mxcnt = b.mxcnt;
            res.mx2 = max(a.mx, b.mx2);
        }
        else {
            res.mx = a.mx;
            res.mxcnt = a.mxcnt;
            res.mx2 = max(a.mx2, b.mx);
        }
        return res;
    }

    int sz;
    vector<Node> tree;
    SegBeats(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, {NEG, NEG, 0, -1});
        for (int i = 0; i < n; i++) tree[i | sz] = {i, NEG, 1, -1};
        for (int i = sz - 1; i >= 1; i--) tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    void apply(int node, int s, int e, int val) {
        tree[node].mx = val;
        tree[node].lazy = val;
    }
    void push(int node, int s, int e) {
        if (~tree[node].lazy) {
            int m = s + e >> 1;
            if (tree[node << 1].mx > tree[node].lazy) apply(node << 1, s, m, tree[node].lazy);
            if (tree[node << 1 | 1].mx > tree[node].lazy) apply(node << 1 | 1, m + 1, e, tree[node].lazy);
            tree[node].lazy = -1;
        }
    }
    void chmin(int node, int s, int e, int l, int r, int val) {
        if (l > e || s > r || tree[node].mx <= val) return;
        if (l <= s && e <= r && tree[node].mx2 < val) {
            seg.upd(val + 1, tree[node].mx, -tree[node].mxcnt);
            apply(node, s, e, val);
            return;
        }
        push(node, s, e);
        int m = s + e >> 1;
        chmin(node << 1, s, m, l, r, val);
        chmin(node << 1 | 1, m + 1, e, l, r, val);
        tree[node] = op(tree[node << 1], tree[node << 1 | 1]);
    }
    void chmin(int l, int r, int val) { chmin(1, 0, sz - 1, l, r, val); }
    void assign(int node, int s, int e, int i, int val) {
        if (e < i || i < s) return;
        if (s == e) {
            tree[node] = {val, NEG, 1, -1};
            return;
        }
        push(node, s, e);
        int m = s + e >> 1;
        assign(node << 1, s, m, i, val);
        assign(node << 1 | 1, m + 1, e, i, val);
        tree[node] = op(tree[node << 1], tree[node << 1 | 1]);
    }
    void assign(int i, int val) { assign(1, 0, sz - 1, i, val); }
    int get(int node, int s, int e, int i) {
        if (s == e) return tree[node].mx;
        push(node, s, e);
        int m = s + e >> 1;
        if (i <= m) return get(node << 1, s, m, i);
        return get(node << 1 | 1, m + 1, e, i);
    }
    int get(int i) { return get(1, 0, sz - 1, i); }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    seg = Seg(n);
    SegBeats right(n);
    while (q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            --a, --b;
            if (a) right.chmin(0, a - 1, a - 1);

            int old = right.get(a);
            seg.upd(a, old, -1);
            right.assign(a, b);
            seg.upd(a, b, 1);
        }
        else cout << seg.qry(a - 1, b - 1) << "\n";
    }

    return 0;
}
