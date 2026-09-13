#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, k;
    ll mod;
    cin >> n >> m >> k >> mod;

    constexpr int N = 100;
    static ll comb[N + 1][N + 1] = {1};
    for (int i = 1; i <= N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            if (comb[i][j] >= mod) comb[i][j] -= mod;
        }
    }

    vector<ll> fac(n + 1, 1 % mod);
    for (int i = 2; i <= n; i++) fac[i] = fac[i - 1] * i % mod;

    vector dp(n + 1, vector(m + 1, vector<ll>(n + 1, -1)));
    auto f = [&](auto &&f, int n, int m, int k) -> ll {
        auto &res = dp[n][m][k];
        if (~res) return res;
        res = 0;

        if (k && n < m - 1 + k) return 0;
        // k > 2^(m-1)이면 안됨
        if (m < 8 && k > (1 << m - 1)) return 0;

        if (!n) {
            if (!k) return res = 1 % mod;
            else return 0;
        }
        if (m <= 1) {
            if (k == m) return res = fac[n];
            else return 0;
        }

        for (int i = 1; i <= n; i++) {
            int l = i - 1;
            int r = n - i;
            ll sum = 0;
            for (int k1 = max(0, k - r); k1 <= min(l, k); k1++) {
                int k2 = k - k1;
                sum += f(f, l, m - 1, k1) * f(f, r, m - 1, k2);
                sum %= mod;
            }
            res += sum * comb[n - 1][l];
            res %= mod;
        }
        return res;
    };

    cout << f(f, n, m, k);

    return 0;
}
