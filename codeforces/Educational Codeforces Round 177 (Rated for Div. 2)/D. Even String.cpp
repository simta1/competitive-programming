#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
void add(ll &a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

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

    constexpr ll MOD = 998'244'353;
    constexpr int N = 5e5 + 5;
    static ll fac[N + 1] = {1}, facInv[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    facInv[N] = modInv(fac[N], MOD);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    auto nCr = [&](int n, int r) {
        return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
    };

    int TC;
    for (cin >> TC; TC--;) {
        int c[26], n = 0;
        for (int i = 0; i < 26; i++) {
            cin >> c[i];
            n += c[i];
        }

        int lo = n >> 1;
        int hi = n + 1 >> 1;
        vector<ll> dp(lo + 1);
        dp[0] = 1;

        int used = 0;
        for (int i = 0; i < 26; i++) if (c[i]) {
            vector<ll> ndp(n + 1);
            for (int j = 0; j <= lo; j++) {
                if (!dp[j]) continue;
                if (j + c[i] <= lo) add(ndp[j + c[i]], dp[j] * nCr(lo - j, c[i]) % MOD);
                if (used - j + c[i] <= hi) add(ndp[j], dp[j] * nCr(hi - (used - j), c[i]) % MOD);
            }
            used += c[i];
            swap(dp, ndp);
        }
        cout << dp[lo] << "\n";
    }

    return 0;
}
