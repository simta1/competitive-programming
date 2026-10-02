#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> cnt_len(n + 1);
    auto dfs = [&](auto &&dfs, int l, int r) {
        if (l > r) return;
        ++cnt_len[r - l + 1];
        int m = l + r >> 1;
        dfs(dfs, l, m - 1);
        dfs(dfs, m + 1, r);
    };
    dfs(dfs, 0, n - 1);

    vector<ll> cnt(n + 1);
    auto solve = [&](int len, ll x) {
        vector<int> right(len), left(len);
        auto build = [&](auto &&build, int l, int r) -> void {
            if (l > r) return;
            int m = l + r >> 1;
            right[m] = r - m + 1;
            left[m] = m - l + 1;
            build(build, l, m - 1);
            build(build, m + 1, r);
        };
        int l = 0, r = len - 1, m = l + r >> 1;
        build(build, 0, len - 1);

        unordered_map<int, int> mpl, mpr;
        for (int i = l; i < m; i++) ++mpl[right[i]];
        for (int i = m + 1; i <= r; i++) ++mpr[left[i]];
        for (auto [len1, cnt1] : mpl) {
            for (auto [len2, cnt2] : mpr) {
                cnt[len1 + len2] += ll(cnt1) * cnt2 * x;
            }
        }
    };
    for (int len = 1; len <= n; len++) if (cnt_len[len]) solve(len, cnt_len[len]);

    auto f = [&](auto &&f, int l, int r) -> void {
        if (l >= r) return;
        int m = l + r >> 1;
        for (int i = l; i < m; i++) ++cnt[m - i];
        for (int i = m + 1; i <= r; i++) ++cnt[i - m];

        f(f, l, m - 1);
        f(f, m + 1, r);
    };
    f(f, 0, n - 1);

    for (int k = 0; k <= n; k++) cout << cnt[n - k] << " ";

    return 0;
}
