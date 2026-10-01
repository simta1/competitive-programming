#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<ll> x(n), y(n), c(n);
        for (auto &e : x) cin >> e;
        for (auto &e : y) cin >> e;
        for (auto &e : c) cin >> e;

        constexpr ll INF = 1e17;
        vector<ll> dp(16, -INF);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            vector<ll> ndp(16, -INF);
            for (int mask = 0; mask < 16; mask++) if (dp[mask] != -INF) {
                for (int add = 0; add < 16; add++) {
                    if (mask & add) continue;
                    int nmask = mask | add;
                    ll w = 0;
                    if (add & 1) w -= 2 * x[i];
                    if (add & 2) w += 2 * x[i];
                    if (add & 4) w -= 2 * y[i];
                    if (add & 8) w += 2 * y[i];
                    if (add) w -= c[i];
                    ndp[nmask] = max(ndp[nmask], dp[mask] + w);
                }
            }
            swap(dp, ndp);
        }

        cout << accumulate(c.begin(), c.end(), 0LL) + dp[15] << "\n";
    }

    return 0;
}
