#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k, p;
        cin >> n >> k >> p;

        auto add = [&](ll &a, ll b) {
            a += b;
            if (a >= p) a -= p;
        };

        vector dp(n + 2, vector(2, vector<ll>(k + 1)));
        vector pfs(n + 2, vector(2, vector<ll>(k + 1)));
        dp[0][0] = vector<ll>(k + 1, 1);

        for (int i = 1; i <= n + 1; i++) {
            for (int cnt = 0; cnt < 2; cnt++) {
                for (int val = 0; val <= (i <= n ? k : 0); val++) {
                    dp[i][cnt][val] = dp[i - 1][cnt][k];
                    if (val < k && i >= 2) {
                        dp[i][cnt][val] += (k - val) * dp[i - 2][!cnt][k - val - 1];
                        dp[i][cnt][val] -= pfs[i - 2][!cnt][k - val - 1];
                        dp[i][cnt][val] %= p;
                        if (dp[i][cnt][val] < 0) dp[i][cnt][val] += p;
                    }
                    pfs[i][cnt][val] = dp[i][cnt][val] * val % p;
                }

                for (int val = 1; val <= k; val++) {
                    add(dp[i][cnt][val], dp[i][cnt][val - 1]);
                    add(pfs[i][cnt][val], pfs[i][cnt][val - 1]);
                }
            }
        }

        int ans = dp[n + 1][0][0] - dp[n + 1][1][0];
        if (ans < 0) ans += p;
        cout << ans << "\n";
    }

    return 0;
}
