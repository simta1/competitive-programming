#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k, p;
        cin >> n >> k >> p;

        vector dp(n, vector(k + 1, vector<int>(k + 1)));
        for (int val = 0; val <= k; val++) dp[0][val][0] = 1;

        auto add = [&](int &a, int b) {
            a += b;
            if (a >= p) a -= p;
        };

        for (int i = 1; i < n; i++) {
            for (int cur = 0; cur <= k; cur++) {
                for (int prv = 0; prv <= k; prv++) {
                    int mn = max(0, prv - cur);
                    dp[i][cur][prv] = dp[i - 1][prv][mn];
                }
                for (int j = k - 1; j >= 0; j--) add(dp[i][cur][j], dp[i][cur][j + 1]);
            }
        }

        ll ans = 0;
        for (int cur = 0; cur <= k; cur++) ans += dp[n - 1][cur][cur];
        cout << ans % p << "\n";
    }

    return 0;
}
