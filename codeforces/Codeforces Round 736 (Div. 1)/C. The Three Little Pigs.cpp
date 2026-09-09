#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    constexpr ll MOD = 1e9 + 7;
    auto pow = [&](ll a, ll n) {
        ll res = 1;
        for (; n; n >>= 1) {
            if (n & 1) res = res * a % MOD;
            a = a * a % MOD;
        }
        return res;
    };
    auto modInv = [&](ll a) {
        return pow(a, MOD - 2);
    };

    constexpr int N = 3e6 + 5;
    static ll fac[N + 1] = {1}, facInv[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    facInv[N] = modInv(fac[N]);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;
    auto nCr = [&](int n, int r) {
        return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
    };

    vector<ll> q(3 * n + 2);
    for (int i = 1; i <= 3 * n + 1; i++) q[i] = nCr(3 * n + 3, i);
    q[1] -= 3;
    q[2] -= 3;
    q[3] -= 1;
    for (int i = 1; i <= 3; i++) if (q[i] < 0) q[i] += MOD;

    constexpr ll inv3 = (MOD + 2) / 3;
    vector<ll> p(3 * n + 1);
    p[0] = q[1] * inv3 % MOD;
    p[1] = (q[2] * inv3 - p[0]) % MOD;
    if (p[1] < 0) p[1] += MOD;
    for (int i = 2; i <= 3 * n; i++) {
        p[i] = (q[i + 1] - p[i - 2] - 3 * p[i - 1]) * inv3 % MOD;
        if (p[i] < 0) p[i] += MOD;
    }

    while (m--) {
        int x;
        cin >> x;
        cout << p[x] << "\n";
    }

    return 0;
}
