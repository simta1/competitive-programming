#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;

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

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int z = 0;
        vector<int> v(n);
        for (auto &e : v) {
            cin >> e;
            z += !e;
        }

        int cnt = 0;
        for (int i = 0; i < z; i++) cnt += v[i];

        ll sum = 0;
        for (int i = 1; i <= cnt; i++) sum += modInv(ll(i) * i % MOD);
        sum %= MOD;
        cout << n * ll(n - 1) / 2 % MOD * sum % MOD << "\n";
    }

    return 0;
}
