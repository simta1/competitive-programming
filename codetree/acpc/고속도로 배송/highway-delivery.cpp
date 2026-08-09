#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, bool>> v(2 * n);
    for (int i = 0; i < n; i++) cin >> v[i].first;
    for (int i = 0; i < n; i++) {
        cin >> v[n + i].first;
        v[n + i].second = 1;
    }

    vector<ll> phi(n + 1);
    for (int i = 1; i <= n; i++) cin >> phi[i];

    sort(v.begin(), v.end());

    constexpr ll INF = 1e18;
    vector dp(2, vector<ll>(n + 1, INF));
    dp[0][0] = 0;
    int cnt[2] = {0};
    for (int i = 1; i <= 2 * n; i++) {
        fill(dp[i & 1].begin(), dp[i & 1].end(), INF);
        ++cnt[v[i - 1].second];
        int mn = abs(cnt[0] - cnt[1]);
        int mx = min(i, 2 * n - i);
        for (int c = mn; c <= mx; c++) {
            ll dist = i == 1 ? 0 : (v[i - 1].first - v[i - 2].first);
            if (c && dp[i - 1 & 1][c - 1] != INF) dp[i & 1][c] = min(dp[i & 1][c], dp[i - 1 & 1][c - 1] + phi[c - 1] * dist);
            if (c + 1 <= n && dp[i - 1 & 1][c + 1] != INF) dp[i & 1][c] = min(dp[i & 1][c], dp[i - 1 & 1][c + 1] + phi[c + 1] * dist);
        }
    }
    cout << dp[0][0];

    return 0;
}