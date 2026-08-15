#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using mat = array<array<ll, 6>, 6>;
constexpr ll MOD = 998'244'353;

mat op(const mat &a, const mat &b) {
    mat res{};
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 6; i++) {
            for (int k = 0; k < 6; k++) {
                res[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            res[i][j] %= MOD;
        }
    }
    return res;
}

mat binpow(mat a, ll n) {
    mat res{};
    for (int i = 0; i < 6; i++) res[i][i] = 1;
    for (; n; n >>= 1) {
        if (n & 1) res = op(res, a);
        a = op(a, a);
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll inv2 = MOD + 1 >> 1;
    constexpr ll inv100 = 828542813; 

    int TC;
    for (cin >> TC; TC--;) {
        ll n, p;
        cin >> n >> p;
        p = p * inv100 % MOD;
        ll q = 1 - p;
        if (q < 0) q += MOD;
        mat a = {{
            {p, 0, 0, q, 0, 0},
            {p, p, 0, q, q, 0},
            {p, 2 * p, p, q, 2 * q, q},
            {q, 0, 0, p, 0, 0},
            {0, q, 0, 0, p, 0},
            {0, 0, q, 0, 0, p}
        }};
        mat x = binpow(a, n - 2);
        ll dp[6] = {0};
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) dp[i] += x[i][j];
        }
        ll E_l2 = (dp[2] + dp[5]) % MOD;
        ll E_l = (dp[1] + dp[4]) % MOD;
        n %= MOD;
        ll ans = E_l2 - (n - 1) * E_l + (n * n - n) % MOD * inv2;
        ans %= MOD;
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}
