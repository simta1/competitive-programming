#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    int sz = 1;
    while (sz < n) sz <<= 1;
    vector<vector<int>> tree(sz << 1);

    for (int _ = q; _--;) {
        int l, r, x;
        cin >> l >> r >> x;
        for (--l |= sz, --r |= sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) tree[l++].push_back(x);
            if (~r & 1) tree[r--].push_back(x);
        }
    }

    vector<int> cnt(q + 1);
    int ans = 0;
    auto f = [&](auto &&f, int node, int s, int e) -> void {
        if (s >= n) return;

        for (auto x : tree[node]) {
            ans += (++cnt[x] == 1);
        }

        if (s != e) {
            int m = s + e >> 1;
            f(f, node << 1, s, m);
            f(f, node << 1 | 1, m + 1, e);
        }
        else cout << ans << " ";

        for (auto x : tree[node]) {
            if (--cnt[x] == 0) --ans;
        }
    };
    f(f, 1, 0, sz - 1);

    return 0;
}
