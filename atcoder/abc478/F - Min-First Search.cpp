#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg {
    int sz;
    vector<ll> tree, lm, la;
    static constexpr ll MOD = 998'244'353;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1);
        lm.resize(sz << 1, 1);
        la.resize(sz << 1);
        // for (int i = 0; i < n; i++) cin >> tree[i | sz];
        // for (int i = sz - 1; i > 0; i--) {
        //     tree[i] = tree[i << 1] + tree[i << 1 | 1];
        //     if (tree[i] >= MOD) tree[i] -= MOD;
        // }
    }
    void apply(int node, int s, int e, ll m, ll a) {
        tree[node] = (tree[node] * m + (e - s + 1) * a) % MOD;
        lm[node] = lm[node] * m % MOD;
        la[node] = (la[node] * m + a) % MOD;
    }
    void push(int node, int s, int e) {
        if (lm[node] != 1 || la[node]) {
            int m = s + e >> 1;
            apply(node << 1, s, m, lm[node], la[node]);
            apply(node << 1 | 1, m + 1, e, lm[node], la[node]);
            lm[node] = 1;
            la[node] = 0;
        }
    }
    void upd(int node, int s, int e, int l, int r, ll mul, ll add) {
        if (l <= s && e <= r) {
            apply(node, s, e, mul, add);
            return;
        }
        if (l > e || s > r) return;
        push(node, s, e);
        int m = s + e >> 1;
        upd(node << 1, s, m, l, r, mul, add);
        upd(node << 1 | 1, m + 1, e, l, r, mul, add);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
        if (tree[node] >= MOD) tree[node] -= MOD;
    }
    void upd(int l, int r, ll mul, ll add) { upd(1, 0, sz - 1, l, r, mul, add); }
    ll qry(int node, int s, int e, int l, int r) {
        if (l <= s && e <= r) return tree[node];
        if (l > e || s > r) return 0;
        push(node, s, e);
        int m = s + e >> 1;
        ll res = qry(node << 1, s, m, l, r) + qry(node << 1 | 1, m + 1, e, l, r);
        return res >= MOD ? (res - MOD) : res;
    }
    ll qry(int l, int r) { return qry(1, 0, sz - 1, l, r); }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    Seg seg(n + 1);
    seg.upd(0, 0, 1, 1);

    ll ans = 1;
    for (int i = 1; i < n; i++) {
        int cnt = seg.qry(0, v[i]);
        ans = ans * cnt % MOD;
        seg.upd(0, v[i], 0, 0);
        seg.upd(v[i], v[i], 0, cnt);
        seg.upd(0, 0, 1, 1);
    }

    cout << ans << "\n";

    return 0;
}
