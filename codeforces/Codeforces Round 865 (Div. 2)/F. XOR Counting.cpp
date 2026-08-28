#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll n);
ll g(ll n);

constexpr ll MOD = 998'244'353;

map<ll, ll> a, b;
ll f(ll n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (a.count(n)) return a[n];
    if (n & 1) a[n] = 2 * f(n / 2) + g(n / 2);
    else a[n] = 2 * f(n / 2) + 2 * f(n / 2 - 1);
    a[n] %= MOD;
    return a[n];
}
ll g(ll n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (b.count(n)) return b[n];
    if (n & 1) b[n] = g(n / 2);
    else b[n] = g(n / 2) + g(n / 2 - 1);
    b[n] %= MOD;
    return b[n];
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll n;
        int m;
        cin >> n >> m;

        if (m == 1) cout << n % MOD << "\n";
        else if (m >= 3) {
            ll k = n / 2 % MOD;
            if (n & 1) cout << (k + 1) * (k + 1) % MOD << "\n";
            else cout << k * (k + 1) % MOD << "\n";
        }
        else cout << f(n) << "\n";
    }

    return 0;
}
