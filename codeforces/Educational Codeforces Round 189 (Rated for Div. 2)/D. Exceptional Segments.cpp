#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll n, ll r) {
    return (n - r >> 2) + 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;

    int TC;
    for (cin >> TC; TC--;) {
        ll n, x;
        cin >> n >> x;
        cout << (f(x, 0) % MOD * ((f(n, 3) - f(x - 1, 3)) % MOD) + f(x, 2) % MOD * ((f(n, 1) - f(x - 1, 1)) % MOD)) % MOD << "\n";
    }

    return 0;
}
