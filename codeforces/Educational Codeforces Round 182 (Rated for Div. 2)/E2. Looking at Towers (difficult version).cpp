#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        auto comp = v;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (auto &e : v) e = lower_bound(comp.begin(), comp.end(), e) - comp.begin() + 1;

        vector<int> l, r;
        for (auto e : v) {
            if (l.empty() || l.back() < e) l.push_back(e);
        }
        for (int i = n - 1; i >= 0; i--) {
            if (r.empty() || r.back() < v[i]) r.push_back(v[i]);
        }

        int sz = 1;
        while (sz < comp.size() + 1) sz <<= 1;
        vector<ll> tree(sz << 1), lm(sz << 1, 1), la(sz << 1);
        auto propagate = [&](int node, int s, int e) {
            if (lm[node] != 1 || la[node]) {
                tree[node] = (tree[node] * lm[node] + (e - s + 1) * la[node]) % MOD;
                if (s != e) {
                    for (auto nxt : {node << 1, node << 1 | 1}) {
                        lm[nxt] = lm[nxt] * lm[node] % MOD;
                        la[nxt] = (la[nxt] * lm[node] + la[node]) % MOD;
                    }
                }
                lm[node] = 1;
                la[node] = 0;
            }
        };
        auto update = [&](auto &&update, int node, int s, int e, int l, int r, ll mul, ll add) {
            propagate(node, s, e);
            if (l <= s && e <= r) {
                lm[node] = mul;
                la[node] = add;
                propagate(node, s, e);
                return;
            }
            if (l > e || s > r) return;
            int m = s + e >> 1;
            update(update, node << 1, s, m, l, r, mul, add);
            update(update, node << 1 | 1, m + 1, e, l, r, mul, add);
            tree[node] = tree[node << 1] + tree[node << 1 | 1];
            if (tree[node] >= MOD) tree[node] -= MOD;
        };
        auto query = [&](auto &&query, int node, int s, int e, int l, int r) {
            propagate(node, s, e);
            if (l <= s && e <= r) return tree[node];
            if (l > e || s > r) return 0LL;
            int m = s + e >> 1;
            ll res = query(query, node << 1, s, m, l, r) + query(query, node << 1 | 1, m + 1, e, l, r);
            return res >= MOD ? (res - MOD) : res;
        };

        update(update, 1, 0, sz - 1, 0, 0, 1, 1);
        vector<ll> dp(n + 1);
        for (int i = 0; i < n; i++) {
            int cur = v[i];
            auto it = lower_bound(l.begin(), l.end(), cur);
            if (it != l.end() && *it == cur) {
                int prv = it == l.begin() ? 0 : *prev(it);
                update(update, 1, 0, sz - 1, cur, cur, 1, query(query, 1, 0, sz - 1, cur, cur));
                update(update, 1, 0, sz - 1, cur, cur, 1, query(query, 1, 0, sz - 1, prv, prv));
            }
            update(update, 1, 0, sz - 1, cur + 1, comp.size(), 2, 0);
            dp[i + 1] = query(query, 1, 0, sz - 1, comp.size(), comp.size());
        }

        fill(tree.begin(), tree.end(), 0);
        fill(lm.begin(), lm.end(), 1);
        fill(la.begin(), la.end(), 0);
        update(update, 1, 0, sz - 1, 0, 0, 1, 1);
        vector<ll> rdp(n);
        for (int i = 0; i < n; i++) {
            int cur = v[n - 1 - i];
            auto it = lower_bound(r.begin(), r.end(), cur);
            if (it != r.end() && *it == cur) {
                int prv = it == r.begin() ? 0 : *prev(it);
                if (cur == comp.size()) rdp[n - 1 - i] = query(query, 1, 0, sz - 1, prv, prv);
                update(update, 1, 0, sz - 1, cur, cur, 1, query(query, 1, 0, sz - 1, cur, cur));
                update(update, 1, 0, sz - 1, cur, cur, 1, query(query, 1, 0, sz - 1, prv, prv));
            }
            update(update, 1, 0, sz - 1, cur + 1, comp.size(), 2, 0);
        }

        ll ans = 0;
        for (int r = 0; r < n; r++) if (v[r] == comp.size()) {
            ans += (dp[r + 1] - dp[r]) * rdp[r];
            ans %= MOD;
        }
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}
