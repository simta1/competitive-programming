#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(int x, int y) {
    int a = x / 2;
    int b = y / 2;
    return a << 1 | b;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // for (int x1 = 0; x1 < 4; x1 += 2) {
    //     for (int y1 = 0; y1 < 4; y1 += 2) {
    //         for (int x2 = 0; x2 < 4; x2 += 2) {
    //             for (int y2 = 0; y2 < 4; y2 += 2) {
    //                 int g1 = !x1 && !y1 ? 0 : 2;
    //                 int g2 = !x2 && !y2 ? 0 : 2;
    //                 int g3 = (x1 == x2) && (y1 == y2) ? 0 : 2;
    //                 int A2 = (x1 * y2 - x2 * y1) % 4 == 0 ? 0 : 2;
    //                 int B = (g1 + g2 + g3) % 4;
    //                 if (A2 == B) {
    //                     // cout << x1 << " " << y1 << " " << x2 << " " << y2 << "::\n";
    //                     cout << f(x1, y1) << " " << f(x2, y2) << "\n";
    //                 }
    //             }
    //         }
    //     }
    // }

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll cnt[4]{};
        for (int j = 0; j < n; j++) if (i != j) {
            int dx = abs(v[i].first - v[j].first) & 3;
            int dy = abs(v[i].second - v[j].second) & 3;
            ++cnt[f(dx, dy)];
        }

        for (int mask = 0; mask < 4; mask++) ans += cnt[mask] * (cnt[mask] - 1) / 2;
        ans += cnt[0] * (cnt[1] + cnt[2] + cnt[3]);
    }
    assert(ans % 3 == 0);
    cout << ans / 3;

    return 0;
}
