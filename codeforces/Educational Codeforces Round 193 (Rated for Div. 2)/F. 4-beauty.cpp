#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void chmin(ll &a, ll b) {
    a = min(a, b);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int pw2[20] = {1}, pw3[15] = {1};
    for (int i = 1; i < 20; i++) pw2[i] = pw2[i - 1] * 2;
    for (int i = 1; i < 15; i++) pw3[i] = pw3[i - 1] * 3;

    vector<vector<pair<int, int>>> v(n / 4 + 1);
    for (int i = 1; i <= n; i++) {
        int a = 0, b = 0;
        int x = i;
        while (x % 2 == 0) ++a, x /= 2;
        while (x % 3 == 0) ++b, x /= 3;
        if (x <= n / 4) v[x].emplace_back(a, b);
    }

    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++) cin >> m[i];

    ll ans = 0;
    for (int x = 1; x <= n / 4; x++) if (!v[x].empty()) {
        sort(v[x].begin(), v[x].end());
        int mxa = 0, mxb = 0;
        for (auto [a, b] : v[x]) {
            mxa = max(mxa, a);
            mxb = max(mxb, b);
        }
        if (mxa <= 1) continue;
        constexpr ll INF = 1e18;
        vector<ll> dp(1 << mxa + 1, INF);
        int full = (1 << mxa + 1) - 1;
        dp[0] = m[x];
        dp[1] = 0;
        for (int b = 0; b <= mxb; b++) {
            for (int a = 0; a <= mxa; a++) {
                vector<ll> ndp(1 << mxa + 1, INF);
                if (b == mxb && a == mxa) continue;
                for (int mask = 0; mask < (1 << mxa + 1); mask++) {
                    if (dp[mask] == INF) continue;
                    int na = a + 1, nb = b;
                    if (a == mxa) na = 0, nb = b + 1;
                    ll val = ll(x) * pw2[na] * pw3[nb];
                    int cost = val > n ? 0 : m[val];
                    int nmask = mask << 1 & full;
                    chmin(ndp[nmask], dp[mask] + cost);
                    if (na >= mxa - 1 || (mask >> mxa - 2) != 7) chmin(ndp[nmask | 1], dp[mask]);
                }
                swap(ndp, dp);
            }
        }
        ans += *min_element(dp.begin(), dp.end());
    }
    cout << ans;

    return 0;
}
