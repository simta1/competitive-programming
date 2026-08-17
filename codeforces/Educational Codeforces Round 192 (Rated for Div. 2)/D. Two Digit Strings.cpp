#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string s, t;
        cin >> s >> t;

        int n = s.size();
        int m = t.size();
        vector<int> a(n + 1), b(m + 1);
        for (int i = 1; i <= n; i++) {
            a[i] = s[i - 1] - '0';
            a[i] += a[i - 1];
            if (a[i] >= 10) a[i] -= 10;
        }
        for (int i = 1; i <= m; i++) {
            b[i] = t[i - 1] - '0';
            b[i] += b[i - 1];
            if (b[i] >= 10) b[i] -= 10;
        }

        if (a[n] != b[m]) {
            cout << "-1\n";
            continue;
        }

        vector dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i] == b[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        cout << dp[n][m] << "\n";
    }

    return 0;
}
