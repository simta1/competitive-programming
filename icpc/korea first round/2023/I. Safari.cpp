#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<array<int, 4>> v(n);
    for (auto &[e, s, x, y] : v) cin >> x >> y;
    for (auto &[e, s, x, y] : v) cin >> s >> e;
    v.push_back({0, 0, 0, 0});

    sort(v.begin(), v.end());

    constexpr int INF = 2e9;
    vector<int> dp(n + 1, -INF);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) if (dp[j] != -INF) {
            auto [pe, ps, px, py] = v[j];
            auto [ce, cs, cx, cy] = v[i];
            int t = max(abs(px - cx) + abs(py - cy) + pe, cs);
            if (t > ce) continue;
            dp[i] = max(dp[i], dp[j] + ce - t);
        }
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
