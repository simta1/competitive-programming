#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using pll = pair<ll, ll>;
ll f(pll &a, pll &b, pll &c) {
    ll x1 = a.first - b.first;
    ll y1 = a.second - b.second;
    ll x2 = a.first - c.first;
    ll y2 = a.second - c.second;
    return x1 * y2 - x2 * y1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<pair<ll, ll>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    auto check = [&](ll x) {
        vector dp(n, vector<pair<int, ll>>(n));
        for (int len = 3; len <= n; len++) {
            for (int s = 0, e = len - 1; e < n; ++s, ++e) {
                for (int m = s + 1; m < e; m++) {
                    auto [cnt1, area1] = dp[s][m];
                    auto [cnt2, area2] = dp[m][e];
                    int c = cnt1 + cnt2;
                    ll area = area1 + area2 + f(v[s], v[m], v[e]);
                    pair<int, ll> cur = area >= x ? pair{c + 1, 0LL} : pair{c, area};
                    dp[s][e] = max(dp[s][e], cur);
                }
            }
        }
        return dp[0][n - 1].first >= k + 1;
    };

    ll lo = 0, hi = 1e17;
    while (lo + 1 < hi) {
        ll mid = lo + hi >> 1;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo;

    return 0;
}
