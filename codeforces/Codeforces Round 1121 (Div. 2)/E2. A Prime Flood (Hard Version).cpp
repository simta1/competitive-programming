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
    constexpr ll inv2 = MOD + 1 >> 1;

    constexpr int N = 3e5;
    static ll pow[N + 1] = {1}, ipow[N + 1] = {1};
    for (int i = 1; i <= N; i++) pow[i] = pow[i - 1] * 2 % MOD;
    for (int i = 1; i <= N; i++) ipow[i] = ipow[i - 1] * inv2 % MOD;

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

    static vector<int> js[N + 1];
    for (int j = 1; j <= N; j++) {
        for (int i = a[j]; i < j; i += a[j]) js[i].push_back(j);
    }
    // int cnt = 0;
    // for (int i = 1; i <= N; i++) cnt += js[i].size();
    // cout << cnt << "\n";

    static set<pair<int, int>> dp[N + 1];
    dp[1] = {{1, 1}};
    for (int i = 2; i <= N; i++) {
        dp[i] = {{i, i}};
        for (auto j : js[i]) {
            int val1 = prev(dp[i - 1].lower_bound(pair{j, -1}))->second;
            int val2 = prev(dp[i].lower_bound(pair{j, -1}))->second;
            if (val2 != val1) dp[i].emplace(j, val1);
        }
    }

    // for (auto [idx, val] : dp[1]) cout << idx << " " << val << "\n";
    // for (auto [idx, val] : dp[2]) cout << idx << " " << val << "\n";
    // for (auto [idx, val] : dp[3]) cout << idx << " " << val << "\n";
    // int mx = 0;
    // for (int i = 1; i <= N; i++) mx = max<int>(mx, dp[i].size());
    // cout << mx << "\n";

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n), cnt(n + 1);
        for (auto &e : v) cin >> e, ++cnt[e];

        auto pfc = cnt;
        for (int i = 1; i <= n; i++) pfc[i] += pfc[i - 1];

        vector<ll> pfs(n + 1);
        for (int y = 1; y <= n; y++) {
            pfs[y] = pfs[y - 1] + (pow[cnt[y]] - 1) * pow[pfc[y - 1]];
            pfs[y] %= MOD;
        }

        ll ans = 0;
        for (int x = 1; x <= n; x++) {
            ans += x * (pow[cnt[x]] - 1);
            ans %= MOD;

            auto [pidx, pval] = *dp[x].begin();
            ++pidx;

            ll sum = 0;
            for (auto [idx, val] : dp[x]) if (idx != x) {
                if (idx > n) idx = n + 1;
                sum += pval * (pfs[idx - 1] - pfs[pidx - 1]);
                sum %= MOD;
                pidx = idx;
                pval = val;
                if (idx == n + 1) break;
            }
            if (pidx <= n) {
                sum += pval * (pfs[n] - pfs[pidx - 1]);
                sum %= MOD;
            }

            ans += sum * (pow[cnt[x]] - 1) % MOD * ipow[pfc[x]];
            ans %= MOD;
        }
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}
