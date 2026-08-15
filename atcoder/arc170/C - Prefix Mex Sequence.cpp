#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
void add(ll &a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector dp(n + 1, vector<ll>(n + 1));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        if (v[i]) {
            for (int j = 0; j < min(n, m + 1); j++) add(dp[i + 1][j + 1], dp[i][j]);
        }
        else {
            for (int j = 0; j <= min(n, m + 1); j++) {
                add(dp[i + 1][j], dp[i][j] * j % MOD);
                if (m - j > 0 && j + 1 <= n) add(dp[i + 1][j + 1], dp[i][j] * (m - j) % MOD);
            }
        }
    }

    ll ans = 0;
    for (int j = 0; j <= n; j++) ans += dp[n][j];
    cout << ans % MOD;


    return 0;
}
