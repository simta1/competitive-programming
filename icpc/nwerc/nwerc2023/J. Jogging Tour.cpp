#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, ll>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    using ld = double;
    ld INF = 1/.0;
    auto f = [&](ld dx, ld dy) {
        auto dist = [&](pair<ll, ll> &a, pair<ll, ll> &b) {
            ll x = a.first - b.first;
            ll y = a.second - b.second;
            return abs(x * dx + y * dy) + abs(x * dy - y * dx);
        };
        vector dp(1 << n, vector<ld>(n, INF));
        for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
        for (int mask = 3; mask < (1 << n); mask++) if (__builtin_popcount(mask) > 1) {
            for (int tmp = mask; tmp; tmp &= tmp - 1) {
                int cur = __builtin_ctz(tmp);
                int pmask = mask ^ (1 << cur);
                for (int tmp2 = pmask; tmp2; tmp2 &= tmp2 - 1) {
                    int prv = __builtin_ctz(tmp2);
                    dp[mask][cur] = min(dp[mask][cur], dp[pmask][prv] + dist(v[prv], v[cur]));
                }
            }
        }
        return *min_element(dp.back().begin(), dp.back().end());
    };

    ld ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld dx = v[j].first - v[i].first;
            ld dy = v[j].second - v[i].second;
            ld len = sqrt(dx * dx + dy * dy);
            dx /= len;
            dy /= len;
            ans = min(ans, f(dx, dy));
        }
    }
    cout << fixed << setprecision(12) << ans;

    return 0;
}
