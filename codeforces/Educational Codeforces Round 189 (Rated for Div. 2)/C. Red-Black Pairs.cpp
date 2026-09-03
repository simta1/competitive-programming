#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string a, b;
        cin >> a >> b;

        vector<int> dp(n);
        dp[0] = a[0] != b[0];
        if (1 < n) dp[1] = min(dp[0] + (a[1] != b[1]), (a[0] != a[1]) + (b[0] != b[1]));
        for (int i = 2; i < n; i++) {
            dp[i] = min(dp[i - 1] + (a[i] != b[i]), dp[i - 2] + (a[i] != a[i - 1]) + (b[i] != b[i - 1]));
        }
        cout << dp[n - 1] << "\n";
    }

    return 0;
}
