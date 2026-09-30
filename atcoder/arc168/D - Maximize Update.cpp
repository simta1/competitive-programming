#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> v(m);
    vector cnt(n, vector<int>(n));
    for (auto &[l, r] : v) {
        cin >> l >> r;
        --l, --r;
        ++cnt[l][r];
    }

    for (int len = 2; len <= n; len++) {
        for (int s = 0, e = len - 1; e < n; ++s, ++e) {
            cnt[s][e] += cnt[s][e - 1] + cnt[s + 1][e] - (len >= 3 ? cnt[s + 1][e - 1] : 0);
        }
    }

    auto f = [&](int l, int r, int m) {
        return cnt[l][r] - (l < m ? cnt[l][m - 1] : 0) - (m < r ? cnt[m + 1][r] : 0) > 0;
    };

    vector dp(n, vector<int>(n, -1));
    auto gdp = [&](auto &&gdp, int l, int r) -> int {
        if (l > r) return 0;
        auto &res = dp[l][r];
        if (~res) return res;
        res = 0;
        for (int m = l; m <= r; m++) res = max(res, gdp(gdp, l, m - 1) + gdp(gdp, m + 1, r) + f(l, r, m));
        return res;
    };
    cout << gdp(gdp, 0, n - 1);

    return 0;
}
