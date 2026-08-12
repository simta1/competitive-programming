#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;
    auto add = [&](ll &a, ll b) {
        a += b;
        if (a >= MOD) a -= MOD;
    };

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        vector<array<ll, 2>> dp(n);
        dp[0][0] = dp[0][1] = 1;
        for (int i = 1; i < n; i++) {
            if (a[i - 1] <= a[i] && b[i - 1] <= b[i]) {
                add(dp[i][0], dp[i - 1][0]);
                add(dp[i][1], dp[i - 1][1]);
            }
            if (a[i - 1] <= b[i] && b[i - 1] <= a[i]) {
                add(dp[i][0], dp[i - 1][1]);
                add(dp[i][1], dp[i - 1][0]);
            }
        }

        cout << (dp[n - 1][0] + dp[n - 1][1]) % MOD << "\n";
    }

    return 0;
}
