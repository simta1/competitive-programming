#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector a(n, vector<ll>(n / 3));
    for (int i = 0; i < n; i++) {
        vector<ll> v(n);
        for (auto &e : v) cin >> e;
        for (int i = 1; i < n; i++) v[i] += v[i - 1];

        vector<ll> dp(n);
        for (int cnt = 1; cnt <= n / 3; cnt++) {
            vector<ll> ndp(n);
            int j = cnt * 3 - 1;
            ndp[j] = v[j];
            for (++j; j < n; ++j) ndp[j] = max(ndp[j - 1], dp[j - 3] + v[j] - v[j - 3]);
            a[i][cnt - 1] = ndp[n - 1];
            swap(dp, ndp);
        }
        for (int j = n / 3 - 1; j > 0; j--) a[i][j] -= a[i][j - 1];
    }

    ll ans = 0;
    priority_queue<array<ll, 3>> pq;
    for (int i = 0; i < n; i++) pq.push({a[i][0], i, 0});
    while (!pq.empty() && k) {
        auto [val, i, j] = pq.top();
        pq.pop();
        --k;
        ans += val;
        if (j + 1 < n / 3) pq.push({a[i][j + 1], i, j + 1});
    }

    cout << ans;

    return 0;
}
