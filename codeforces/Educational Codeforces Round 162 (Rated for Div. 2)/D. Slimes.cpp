#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        vector<ll> pfs(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            pfs[i] = v[i] + pfs[i - 1];
        }

        vector<int> dp(n + 1, -1);
        for (int i = n - 1; i >= 1; i--) {
            if (v[i] == v[i + 1]) dp[i] = dp[i + 1];
            else dp[i] = i + 1;
        }
        vector<int> dp2(n + 1, -1);
        for (int i = 2; i <= n; i++) {
            if (v[i] == v[i - 1]) dp2[i] = dp2[i - 1];
            else dp2[i] = i - 1;
        }

        constexpr int INF = 1e8;
        for (int i = 1; i <= n; i++) {
            int ans = INF;
            if (i < n && pfs[n] - pfs[i] > v[i]) {
                int r = upper_bound(pfs.begin(), pfs.end(), pfs[i] + v[i]) - pfs.begin();
                int cur = INF;
                if (r == i + 1) cur = 1;
                else if (~dp[i + 1]) cur = max(r, dp[i + 1]) - i;
                ans = cur;
            }
            if (i > 1 && pfs[i - 1] > v[i]) {
                int l = lower_bound(pfs.begin(), pfs.end(), pfs[i - 1] - v[i]) - pfs.begin() - 1 + 1;
                int cur = INF;
                if (l == i - 1) cur = 1;
                else if (~dp2[i - 1]) cur = i - min(l, dp2[i - 1]);
                ans = min(ans, cur);
            }
            if (ans == INF) cout << "-1 ";
            else cout << ans << " ";
        }
        cout << "\n";
    }

    return 0;
}
