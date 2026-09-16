#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
tuple<ll, ll, ll> egcd(ll a, ll b) { // ax + by = gcd(a, b)
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = egcd(b, a % b);
    return {y, x - (a / b) * y, g};
}
ll modInv(ll a, ll b) {
    auto [x, y, g] = egcd(a, b);
    return g != 1 ? -1 : (x + b) % b;
} // modInv(n, MOD)

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 35;
    static ll fac[N + 1] = {1}, facInv[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    facInv[N] = modInv(fac[N], MOD);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    auto nCr = [&](int n, int r) {
        return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
    };

    int n, m;
    cin >> n >> m;

    vector dp(n + 1, vector(n + 1, vector<ll>(m + 1)));
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int a = 0; a <= i; a++) {
            int b = i - a;
            for (int cnt = 0; cnt <= m; cnt++) {
                if (!dp[i][a][cnt]) continue;
                for (int add = 0; add <= a && cnt + add <= m; add++) {
                    dp[i + 1][a + 1][cnt + add] += dp[i][a][cnt] * nCr(a, add);
                    dp[i + 1][a + 1][cnt + add] %= MOD;
                }
                for (int add = 0; add <= b && cnt + a + add <= m; add++) {
                    dp[i + 1][a][cnt + a + add] += dp[i][a][cnt] * nCr(b, add);
                    dp[i + 1][a][cnt + a + add] %= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int a = 0; a < n; a++) ans += dp[n][a][m];
    cout << ans % MOD;

    return 0;
}
