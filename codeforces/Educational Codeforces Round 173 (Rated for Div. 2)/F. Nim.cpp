#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<array<int, 51>> pfs(n + 1);
    for (int i = 1; i <= n; i++) {
        ++pfs[i][v[i - 1]];
        for (int a = 0; a <= 50; a++) pfs[i][a] += pfs[i - 1][a];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;

        [&]() {
            int c0 = pfs[r][0] - pfs[l - 1][0];
            if (c0) {
                cout << len - 1 << " " << c0 << "\n";
                return;
            }

            constexpr int INF = 1e9;
            array<pair<ll, int>, 64> dp;
            // pair<ll, int> dp[64]{};
            for (int mask = 0; mask < 64; mask++) dp[mask] = {0, INF};

            bool dup = 0;
            ll ans = 0;
            for (int a = 0; a <= 50; a++) {
                int cnt = pfs[r][a] - pfs[l - 1][a];
                if (cnt >= 2) {
                    dup = 1;
                    ans += cnt * ll(cnt - 1) / 2;
                    ans %= MOD;
                }
                else if (cnt) {
                    auto ndp = dp;
                    if (ndp[a].second > 1) {
                        ndp[a].second = 1;
                        ndp[a].first = 1;
                    }
                    else if (ndp[a].second == 1) {
                        ++ndp[a].first;
                    }

                    for (int mask = 0; mask < 64; mask++) {
                        int nmask = mask ^ a;
                        if (ndp[nmask].second > dp[mask].second + 1) {
                            ndp[nmask].second = dp[mask].second + 1;
                            ndp[nmask].first = dp[mask].first;
                        }
                        else if (ndp[nmask].second == dp[mask].second + 1) {
                            ndp[nmask].first += dp[mask].first;
                            if (ndp[nmask].first >= MOD) ndp[nmask].first -= MOD;
                        }
                    }
                    swap(ndp, dp);
                }
            }

            if (dup) {
                cout << len - 2 << " " << ans << "\n";
                return;
            }

            auto [a, b] = dp[0];
            if (b == INF) cout << "-1\n";
            else cout << len - b << " " << a << "\n";
        }();
    }

    return 0;
}
