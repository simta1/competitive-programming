#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

vector<int> getLpf(int n) {
    vector<int> primes, lpf(n + 1); // least prime factor // O(N)
    for (int i = 2; i <= n; i++) {
        if (!lpf[i]) {
            lpf[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i > n / p) break;
            lpf[i * p] = p;
            if (i % p == 0) break;
        }
    }
    return lpf;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;

    constexpr int N = 3000;
    static ll pow[N + 1] = {1};
    for (int i = 1; i <= N; i++) pow[i] = pow[i - 1] * 2 % MOD;
    for (int i = 0; i <= N; i++) {
        if (--pow[i] < 0) pow[i] += MOD;
    }
    auto lpf = getLpf(N);

    static int a[N + 1];
    for (int i = 1; i <= N; i++) {
        int mul = 1;
        int cur = i;
        while (cur > 1) {
            int p = lpf[cur];
            while (cur % p == 0) cur /= p;
            mul *= p;
        }
        a[i] = mul;
    }

    static int dp[N + 1][N + 1]{};
    for (int i = 1; i <= N; i++) {
        dp[i][i] = i;
        for (int j = i + 1; j <= N; j++) {
            if (i % a[j]) dp[i][j] = dp[i][j - 1];
            else dp[i][j] = dp[i - 1][j - 1];
        }
    }

    // cout << 2 * 3 * 5 * 7 * 13 << "\n";

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n), cnt(n + 1);
        for (auto &e : v) cin >> e, ++cnt[e];

        auto pfs = cnt;
        for (int i = 1; i <= n; i++) pfs[i] += pfs[i - 1];

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += i * pow[cnt[i]];
            ans %= MOD;
            for (int j = i + 1; j <= n; j++) {
                if (cnt[i] && cnt[j]) {
                    ans += dp[i][j] * pow[cnt[i]] % MOD * pow[cnt[j]] % MOD * (pow[pfs[j - 1] - pfs[i]] + 1);
                    ans %= MOD;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
