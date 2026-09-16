#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;

main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 1e9 + 7;

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        for (int k = 1; k <= n; k++) cin >> v[k];

        vector<int> left(n, -1);
        int need = -1;
        vector<int> imos(n);
        for (int k = 1; k <= n; k++) {
            int l = v[k] * k;
            int r = (v[k] + 1) * k;
            if (l < n) ++imos[l];
            if (r < n) --imos[r];

            for (int l = 0, r = k - 1; l < v[k] * k; l += k, r += k) {
                int tmp = min(n - 1, r);
                assert(l <= tmp);
                left[tmp] = max(left[tmp], l);
                need = max(need, l);
            }
        }

        for (int i = 1; i < n; i++) imos[i] += imos[i - 1];
        for (int i = 1; i < n; i++) left[i] = max(left[i], left[i - 1]);

        vector<ll> dp(n), pfs(n);
        if (!imos[0]) dp[0] = pfs[0] = 1;

        for (int i = 1; i < n; i++) {
            if (!imos[i]) {
                int lmax = left[i - 1];
                if (lmax == -1) {
                    dp[i] = 1;
                    lmax = 0;
                }

                dp[i] += pfs[i - 1] - (lmax ? pfs[lmax - 1] : 0);
                dp[i] %= MOD;
                if (dp[i] < 0) dp[i] += MOD;

                pfs[i] = pfs[i - 1] + dp[i];
                if (pfs[i] >= MOD) pfs[i] -= MOD;
            }
            else {
                pfs[i] = pfs[i - 1];
            }
        }

        ll ans = 0;
        if (!~need) {
            ++ans;
            need = 0;
        }
        for (int i = need; i < n; i++) ans += dp[i];
        cout << ans % MOD << "\n";
    }

    return 0;
}
