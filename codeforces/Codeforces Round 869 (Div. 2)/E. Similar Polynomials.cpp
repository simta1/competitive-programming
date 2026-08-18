#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
ll binpow(ll a, ll n) { // a ^ n % mod
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

    ll d;
    cin >> d;

    vector<ll> a(d + 1), b(d + 1);
    for (auto &e : a) cin >> e;
    for (auto &e : b) cin >> e;

    constexpr int N = 2'500'000;
    static ll fac[N + 1] = {1, 1};
    for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    static ll facInv[N + 1]{};
    facInv[N] = modInv(fac[N]);
    for (int i = N - 1; i >= 0; i--) facInv[i] = facInv[i + 1] * (i + 1) % MOD;

    vector<ll> c(d + 1);
    for (int i = 0; i <= d; i++) {
        c[i] = modInv(fac[i] * fac[d - i] % MOD);
        if (d - i & 1) {
            c[i] = -c[i];
            if (c[i] < 0) c[i] += MOD;
        }
    }

    ll a_d = 0, diff = 0;
    for (int i = 0; i <= d; i++) {
        a_d += a[i] * c[i];
        a_d %= MOD;
        diff += (d * (d + 1) / 2 - i) % MOD * c[i] % MOD * (a[i] - b[i]);
        diff %= MOD;
    }
    if (diff < 0) diff += MOD;
    cout << diff * modInv(a_d * d % MOD) % MOD;

    return 0;
}
