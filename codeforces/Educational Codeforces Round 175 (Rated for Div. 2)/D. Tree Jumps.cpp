#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> chd(n + 1);
        vector<int> p(n + 1);
        for (int i = 2; i <= n; i++) {
            cin >> p[i];
            chd[p[i]].push_back(i);
        }

        constexpr ll MOD = 998'244'353;
        auto add = [&](ll &a, ll b) {
            a += b;
            if (a >= MOD) a -= MOD;
        };

        vector<ll> dp(n + 1);
        vector<ll> dpsum(n + 1);
        vector<int> dep(n + 1);
        queue<int> q;
        q.push(1);
        dp[1] = 1;
        dpsum[0] = 1;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (cur != 1) {
                dp[cur] = dpsum[dep[cur] - 1];
                if (p[cur] != 1) {
                    dp[cur] -= dp[p[cur]];
                    if (dp[cur] < 0) dp[cur] += MOD;
                }
                add(dpsum[dep[cur]], dp[cur]);
            }

            for (auto nxt : chd[cur]) {
                dep[nxt] = dep[cur] + 1;
                q.push(nxt);
            }
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += dp[i];
        }
        cout << ans % MOD << "\n";
    }

    return 0;
}
