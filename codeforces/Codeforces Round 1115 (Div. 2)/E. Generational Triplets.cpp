#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // cout << (1LL << 60) << "::\n";

    constexpr ll MOD = 1e9 + 7;
    auto add = [&](ll &a, ll b) {
        a += b;
        if (a >= MOD) a -= MOD;
    };

    constexpr int len = 60;

    int TC;
    for (cin >> TC; TC--;) {
        ll n;
        cin >> n;

        ll dp[len + 1][2][2][4]{};
        dp[0][1][0][0] = 1;
        for (int i = 0; i < len; i++) {
            bool bit = n >> (59 - i) & 1;
            for (int t = 0; t < 2; t++) {
                int mx = t ? bit : 1;
                for (int s = 0; s < 2; s++) {
                    for (int da = 0; da <= mx; da++) {
                        int nt = t && da == mx;
                        int ns = s || da;

                        if (da == 0) add(dp[i + 1][nt][ns][0], dp[i][t][s][0]); // 00->00
                        if (s && da == 0) add(dp[i + 1][nt][ns][1], dp[i][t][s][0]); // 00->01
                        if (da == 1) add(dp[i + 1][nt][ns][2], dp[i][t][s][0]); // 00->10

                        if (s && da == 1) add(dp[i + 1][nt][ns][3], dp[i][t][s][1]); // 01->11
                        if (s && da == 1) add(dp[i + 1][nt][ns][3], dp[i][t][s][2]); // 10->11

                        if (da == 0) add(dp[i + 1][nt][ns][0], dp[i][t][s][3]); // 11->00
                        if (da == 0) add(dp[i + 1][nt][ns][1], dp[i][t][s][3]); // 11->01
                        if (da == 1) add(dp[i + 1][nt][ns][2], dp[i][t][s][3]); // 11->10
                    }
                }
            }
        }

        ll ans = 0;
        for (int t = 0; t < 2; t++) {
            add(ans, dp[len][t][1][0]);
            add(ans, dp[len][t][1][3]);
        }
        cout << ans << "\n";
    }

    return 0;
}
