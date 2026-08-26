#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 998'244'353;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e, --e;

        ll dp[3]{};
        for (auto e : v) {
            if (e == 0) ++dp[0];
            else if (e == 1) {
                dp[1] += dp[0] + dp[1];
                dp[1] %= MOD;
            }
            else {
                dp[2] += dp[1];
                if (dp[2] >= MOD) dp[2] -= MOD;
            }
        }
        cout << dp[2] << "\n";
    }


    return 0;
}
