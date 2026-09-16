#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    vector<ll> tree;
    BIT(int n) : tree(n + 1) {}
    void upd(int i, int add) {
        for (; i < tree.size(); i += i & -i) tree[i] += add;
    }
    ll qry(int l, int r) {
        ll res = 0;
        for (int i = r; i > 0; i -= i & -i) res += tree[i];
        for (int i = l - 1; i > 0; i -= i & -i) res -= tree[i];
        return res;
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n + 1), p(n);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (auto &e : p) cin >> e;

        BIT fw(n);

        set<int> s;
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            int idx = p[i];
            fw.upd(idx, a[idx]);

            auto it = s.upper_bound(idx);
            if (it == s.begin() || fw.qry(*prev(it), idx - 1) < a[idx]) s.insert(idx);
            else idx = *prev(it);

            while (it != s.end() && fw.qry(idx, *it - 1) >= a[*it]) s.erase(it++);
            ans[i] = s.size() - 1;
        }

        for (int i = 0; i < n; i++) cout << ans[i] << " ";
        cout << "\n";
    }

    return 0;
}
