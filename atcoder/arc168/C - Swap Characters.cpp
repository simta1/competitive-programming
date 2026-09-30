#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;
ll pow(ll a, ll n) {
    ll res = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}
ll modInv(ll n) {
    return pow(n, MOD - 2);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 25e4;
    static ll fac[N + 1] = {1}, ifac[N + 1]{};
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[N] = modInv(fac[N]);
    for (int i = N - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;

    int n, k;
    cin >> n >> k;

    string st;
    cin >> st;
    int cnt[3]{};
    for (auto ch : st) ++cnt[ch - 'A'];

    ll ans = 0, ans2 = 0;
    ll A = cnt[0], B = cnt[1], C = cnt[2];
    for (int t = 0; k >= 0; ++t, k -= 2) {
        ll sum = 0;
        for (int x = 0; x <= k; x++) {
            for (int y = 0; x + y <= k; y++) {
                for (int z = 0; x + y + z <= k; z++) {
                    if (x + z + t > A) continue;
                    if (y + x + t > B) continue;
                    if (z + y + t > C) continue;
                    sum += ifac[x]
                        * ifac[z + t] % MOD
                        * ifac[A - x - z - t] % MOD
                        * ifac[y] % MOD
                        * ifac[x + t] % MOD
                        * ifac[B - y - x - t] % MOD
                        * ifac[z] % MOD
                        * ifac[y + t] % MOD
                        * ifac[C - z - y - t];
                    sum %= MOD;
                }
            }
        }
        if (!t) ans += sum;
        else ans2 += sum;
    }

    cout << (ans + 2 * ans2) % MOD
        * fac[A] % MOD
        * fac[B] % MOD
        * fac[C] % MOD << "\n";

    return 0;
}
