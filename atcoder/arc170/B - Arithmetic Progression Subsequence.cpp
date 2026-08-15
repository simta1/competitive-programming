#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e, --e;

    vector<array<int, 10>> nxt(n);

    int last[10]{};
    for (int i = 0; i < 10; i++) last[i] = n;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 10; j++) nxt[i][j] = last[j];
        last[v[i]] = i;
    }

    vector<int> dp(n);
    for (int l = 0; l < n; l++) {
        int r = n;
        for (int d = -4; d <= 4; d++) {
            int v1 = v[l];
            int v2 = v1 + d;
            int v3 = v2 + d;
            if (v3 < 0 || v3 > 9) continue;
            assert(v2 >= 0 && v2 <= 9);
            int idx = nxt[l][v2];
            if (idx == n) continue;
            // cout << idx << "::\n";
            // if (v3 > nxt[idx].size()) cout << v3 << "::\n";
            idx = nxt[idx][v3];
            r = min(r, idx);
        }
        dp[l] = r;
    }
    for (int l = n - 2; l >= 0; l--) dp[l] = min(dp[l], dp[l + 1]);

    ll ans = 0;
    for (int l = 0; l < n; l++) ans += n - dp[l];
    cout << ans;

    return 0;
}
