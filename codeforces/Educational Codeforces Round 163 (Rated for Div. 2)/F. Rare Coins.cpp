#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    constexpr int N = 2'000'005;
    static ll fac[N + 1] = {1}, facInv[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    facInv[N] = modInv(fac[N], MOD);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    auto nCr = [&](int n, int r) {
        return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
    };

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b[i] += b[i - 1];
    }

    vector<ll> pfs(b[n] + 1);
    pfs[0] = 1;
    for (int i = 1; i < pfs.size(); i++) {
        pfs[i] = nCr(b[n], i);
        pfs[i] += pfs[i - 1];
        if (pfs[i] >= MOD) pfs[i] -= MOD;
    }

    constexpr ll inv2 = MOD + 1 >> 1;
    ll pw = 1;
    for (int _ = b[n]; _--;) pw = pw * inv2 % MOD;

    while (q--) {
        int l, r;
        cin >> l >> r;

        int x = b[r] - b[l - 1];
        int y = b[n] - x;
        int d = a[n] - 2 * (a[r] - a[l - 1]);
        if (x <= d) cout << "0\n";
        else cout << pfs[min(x + y, x - d - 1)] * pw % MOD << "\n";
    }

    return 0;
}
