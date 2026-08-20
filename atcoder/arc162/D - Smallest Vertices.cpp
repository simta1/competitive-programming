#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
void add(ll &a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

ll binpow(ll a, ll n) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll modInv(ll a) {
    return binpow(a, MOD - 2);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 505;
    static ll fac[N + 1] = {1, 1};
    for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    static ll facInv[N + 1]{};
    facInv[N] = modInv(fac[N]);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;

    int n;
    cin >> n;

    vector<int> d(n + 1);
    for (int i = 1; i <= n; i++) cin >> d[i];

    ll x = 1;
    for (int i = 1; i <= n; i++) x = x * facInv[d[i]] % MOD;

    ll tot = fac[n - 2] * x % MOD * d[1] % MOD;

    ll ans = 1;
    for (int i = 2; i <= n; i++) if (!d[i]) ++ans;
    ans = ans * tot % MOD;

    vector dp(n + 1, vector<ll>(n + 1));
    dp[0][0] = 1;
    for (int i = n; i >= 2; i--) {
        if (d[i]) {
            for (int sz = d[i] + 1; sz < n; sz++) {
                ll cnt = dp[sz - 1][sz - 1 - d[i]];
                ans += cnt
                    * fac[sz - 2] % MOD
                    * fac[n - sz - 1] % MOD
                    * d[1] % MOD
                    * d[i] % MOD
                    * x;
                ans %= MOD;
            }
        }
        auto ndp = dp;
        for (int cnt = 0; cnt + 1 <= n; cnt++) {
            for (int sum = 0; sum + d[i] <= n; sum++) {
                add(ndp[cnt + 1][sum + d[i]], dp[cnt][sum]);
            }
        }
        swap(ndp, dp);
    }

    cout << ans;

    return 0;
}
