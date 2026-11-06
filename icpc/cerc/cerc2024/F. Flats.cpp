#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg {
    int sz;
    vector<ll> tree, lazy;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1);
        lazy.resize(sz << 1, -1);
    }
    void apply(int node, ll val) {
        tree[node] = lazy[node] = val;
    }
    void push(int node) {
        if (~lazy[node]) {
            apply(node << 1, lazy[node]);
            apply(node << 1 | 1, lazy[node]);
            lazy[node] = -1;
        }
    }
    void upd(int node, int s, int e, int l, int r, ll val) {
        if (l <= s && e <= r) {
            apply(node, val);
            return;
        }
        if (l > e || s > r) return;
        push(node);
        int m = s + e >> 1;
        upd(node << 1, s, m, l, r, val);
        upd(node << 1 | 1, m + 1, e, l, r, val);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }
    void upd(int l, int r, ll val) {
        upd(1, 0, sz - 1, l, r, val);
    }
    ll qry(int node, int s, int e, int l, int r) {
        if (l <= s && e <= r) return tree[node];
        if (l > e || s > r) return 0;
        push(node);
        int m = s + e >> 1;
        return max(qry(node << 1, s, m, l, r), qry(node << 1 | 1, m + 1, e, l, r));
    }
    ll qry(int l, int r) {
        return qry(1, 0, sz - 1, l, r);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, ll>> ps;
    vector<array<ll, 3>> xs, ys;
    Seg seg(2e5);
    int y0_xl = 2e5, y0_xr = 0;
    for (int i = 0; i < n; i++) {
        int l, r, h;
        cin >> l >> r >> h;
        ll mx = seg.qry(l, r - 1);
        if (mx == 0) {
            y0_xr = max(y0_xr, r);
            y0_xl = min(y0_xl, l);
        }
        seg.upd(l, r - 1, mx + h);
        ll x1 = l, x2 = r, y1 = mx, y2 = mx + h;
        ps.emplace_back(x1, y1);
        ps.emplace_back(x1, y2);
        ps.emplace_back(x2, y1);
        ps.emplace_back(x2, y2);

        for (auto x : {x1, x2}) {
            xs.push_back({x, y1, 0});
            xs.push_back({x, y2, 1});
        }
        for (auto y : {y1, y2}) {
            ys.push_back({y, x1, 0});
            ys.push_back({y, x2, 1});
        }
    }
    ys.push_back({0, y0_xl, 0});
    ys.push_back({0, y0_xr, 1});

    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    int V = ps.size();

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    int E = 0;
    for (auto target : {xs, ys}) {
        for (int i = 0, j = 0; i < target.size(); i = j) {
            while (j < target.size() && target[i][0] == target[j][0]) ++j;
            int res = 0, sz = 0;
			ll px = -1;
            int cnt = 0;
            for (int k = i; k < j; k++) {
                auto [_, x, end] = target[k];
				if (px < x) {
					px = x;
					++sz;
				}
                cnt += end ? -1 : 1;
                if (!cnt) {
                    res += sz - 1;
					sz = 0;
                }
            }
            E += res;
        }
    }

    cout << 1 + E - V - n;

    return 0;
}
