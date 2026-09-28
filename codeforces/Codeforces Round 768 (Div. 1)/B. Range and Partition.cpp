#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector<int> v(n), cnt(n + 1);
        for (auto &e : v) cin >> e, ++cnt[e];
        for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];

        int mn = 1e9;
        int x, y;
        for (int l = 1, r = 1; l <= n; l++) {
            while (r <= n && 2 * (cnt[r] - cnt[l - 1]) < n + k) ++r;
            if (r == n + 1) break;
            if (mn > r - l + 1) {
                mn = r - l + 1;
                x = l, y = r;
            }
        }

        int pi = 0, cur = 0;
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; i++) {
            if (v[i] >= x && v[i] <= y) ++cur;
            else --cur;
            if (cur == 1) {
                ans.emplace_back(pi + 1, i + 1);
                pi = i + 1;
                cur = 0;
            }
        }

        cout << x << " " << y << "\n";
        ans.resize(k);
        ans.back().second = n;
        for (auto [a, b] : ans) cout << a << " " << b << "\n";
    }

    return 0;
}
