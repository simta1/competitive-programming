#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        int N = n + 1;
        int sz = 1;
        while (sz < N) sz <<= 1;
        vector<ll> tree(sz << 1), lazy(sz << 1);
        auto propagate = [&](int node, int s, int e) {
            if (lazy[node]) {
                tree[node] += (e - s + 1) * lazy[node];
                if (s != e) {
                    lazy[node << 1] += lazy[node];
                    lazy[node << 1 | 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        };
        function<void(int, int, int, int, int, ll)> update = [&](int node, int s, int e, int l, int r, ll add) {
            propagate(node, s, e);
            if (l <= s && e <= r) {
                lazy[node] = add;
                propagate(node, s, e);
                return;
            }
            if (l > e || s > r) return;
            int m = s + e >> 1;
            update(node << 1, s, m, l, r, add);
            update(node << 1 | 1, m + 1, e, l, r, add);
            tree[node] = tree[node << 1] + tree[node << 1 | 1];
        };
        function<ll(int, int, int, int, int)> query = [&](int node, int s, int e, int l, int r) {
            propagate(node, s, e);
            if (l <= s && e <= r) return tree[node];
            if (l > e || s > r) return 0LL;
            int m = s + e >> 1;
            return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
        };

        ll ans = 0;
        // vector<int> dp(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            ll tmp = query(1, 0, sz - 1, a[i], a[i]) + 1;
            update(1, 0, sz - 1, 0, n, 1);
            if (a[i] == b[i]) {
                // dp[a[i] - 1] = dp[a[i]] + 1;
                ll val = query(1, 0, sz - 1, a[i] - 1, a[i] - 1);
                update(1, 0, sz - 1, a[i] - 1, a[i] - 1, tmp - val);
            }
            else {
                // dp[a[i] - 1] = dp[b[i] - 1] = 0;
                ll val = query(1, 0, sz - 1, a[i] - 1, a[i] - 1);
                update(1, 0, sz - 1, a[i] - 1, a[i] - 1, -val);
                val = query(1, 0, sz - 1, b[i] - 1, b[i] - 1);
                update(1, 0, sz - 1, b[i] - 1, b[i] - 1, -val);
            }

            ans += query(1, 0, sz - 1, 0, 0);
            // ans += dp[0];
        }
        cout << ans << "\n";
    }

    return 0;
}
