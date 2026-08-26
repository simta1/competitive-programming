#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg {
    int sz;
    vector<int> tree;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1, -1);
    }
    void update(int i, int val) { // 0-based
        i |= sz;
        tree[i] = max(tree[i], val);
        while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
    int query(int l, int r) { // 0-based
        int res = -1;
        for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (~r & 1) res = max(res, tree[r--]);
        }
        return res;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<array<int, 3>> v(n);
        vector<int> comp;
        for (int i = 0; i < n; i++) {
            auto &[l, r, idx] = v[i];
            cin >> l >> r;
            idx = i;
            comp.push_back(l);
            comp.push_back(r);
        }
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());

        for (auto &[l, r, idx] : v) {
            l = lower_bound(comp.begin(), comp.end(), l) - comp.begin();
            r = lower_bound(comp.begin(), comp.end(), r) - comp.begin();
        }
        sort(v.begin(), v.end());

        Seg seg(comp.size());
        vector<int> ans(n);
        set<int> rs;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && v[i][0] == v[j][0]) ++j;
            for (int k = i; k < j; k++) {
                auto [l, r, idx] = v[k];
                if (k + 1 < j) {
                    int mn = l;
                    int mx = v[k + 1][1];
                    if (!rs.empty() && *rs.rbegin() >= r) mx = min(mx, *rs.lower_bound(r));
                    ans[idx] = comp[mx] - comp[mn] - (comp[r] - comp[l]);
                }
                else {
                    if (rs.empty() || *rs.rbegin() < r) ans[idx] = 0;
                    else {
                        int mx = *rs.lower_bound(r);
                        int mn = seg.query(r, comp.size() - 1);
                        ans[idx] = comp[mx] - comp[mn] - (comp[r] - comp[l]);
                    }
                }
                seg.update(r, l);
                rs.insert(r);
            }
        }

        for (int i = 0; i < n; i++) cout << ans[i] << "\n";
    }

    return 0;
}
