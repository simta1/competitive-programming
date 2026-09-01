#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    static ll dp[5001];
    dp[0] = 1;
    constexpr ll MOD = 998'244'353;
    for (auto e : v) {
        for (int i = 5000; i >= e; i--) {
            dp[i] += dp[i - e];
            if (dp[i] >= MOD) dp[i] -= MOD;
        }
    }

    ll ans = 0;
    for (int sum = 1; sum <= 5000; sum++) {
        ans += ll(sum + 1) / 2 * dp[sum];
        ans %= MOD;
    }

    for (auto e : v) {
        for (int j = 0; j < e; j++) {
            ans += dp[j] * (e - (e + j + 1) / 2);
            ans %= MOD;
        }
    }
    cout << ans << "\n";

    return 0;
}
