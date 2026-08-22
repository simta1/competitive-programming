#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int v[1005][1005]{}, dp[1005][1005]{};

    int TC;
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++) {
        int n;
        cin >> n;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> v[i][j];
            }
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = max(dp[i][j], (i >= 2 ? dp[i - 2][j] : 0) + v[i][j]);
                dp[i][j] = max(dp[i][j], (j >= 2 ? dp[i][j - 2] : 0) + v[i][j]);
                dp[i][j] = max({
                    dp[i][j], dp[i][j - 1], dp[i - 1][j]
                });
            }
        }

        cout << "Case #" << tc << "\n";
        cout << dp[n][n] << "\n";
    }

    return 0;
}
