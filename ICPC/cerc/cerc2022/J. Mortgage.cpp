#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using Point = pair<ll, ll>;

int ccw(const Point &a, const Point &b, const Point &c) {
    ll x1 = b.first - a.first;
    ll y1 = b.second - a.second;
    ll x2 = c.first - a.first;
    ll y2 = c.second - a.second;
    ll cp = x1 * y2 - x2 * y1;
    return (cp > 0) - (cp < 0);
}

auto convex(vector<Point> &v) {
    vector<Point> res;
    for (auto p : v) {
        while (res.size() >= 2 && ccw(res[res.size() - 2], res[res.size() - 1], p) <= 0) res.pop_back();
        res.push_back(p);
    }
    return res;
}

using hh = __int128;
struct Frac {
    ll a, b; // a/b
    bool operator<(const Frac &o) const {
        return hh(a) * o.b < hh(o.a) * b;
    }
};

Frac slope(const Point &a, const Point &b) {
    return Frac{b.second - a.second, b.first - a.first};
}

Frac f(const vector<Point> &h, const Point &point) {
    int lo = 0, hi = h.size() - 1;
    while (hi - lo >= 3) {
        int p = (2 * lo + hi) / 3, q = (lo + 2 * hi) / 3;
        if (slope(point, h[p]) < slope(point, h[q])) hi = q;
        else lo = p;
    }
    Frac res = {1, 0};
    for (int i = lo; i <= hi; i++) res = min(res, slope(point, h[i]));
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<ll> v(n);
    for (auto &e : v) cin >> e;
    for (int i = 1; i < n; i++) v[i] += v[i - 1];

    int sz = 1;
    while (sz < n) sz <<= 1;

    vector<vector<Point>> tree(sz << 1);
    for (int i = 0; i < n; i++) tree[sz | i] = {{i, v[i]}};
    for (int i = sz - 1; i >= 1; i--) {
        tree[i] = tree[i << 1];
        for (auto e : tree[i << 1 | 1]) tree[i].push_back(e);
        tree[i] = convex(tree[i]);
    }

    auto query = [&](int l, int r, const Point &p) {
        Frac res = {1, 0};
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, f(tree[l++], p));
            if (~r & 1) res = min(res, f(tree[r--], p));
        }
        return res;
    };

    while (m--) {
        int s, k;
        cin >> s >> k;
        --s;
        auto [a, b] = query(s, s + k - 1, {s - 1, s ? v[s - 1] : 0});
        assert(b > 0);

        if (a < 0) cout << "stay with parents\n";
        else cout << a / b << "\n";
    }

    return 0;
}
