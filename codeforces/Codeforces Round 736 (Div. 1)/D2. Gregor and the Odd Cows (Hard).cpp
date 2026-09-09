#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    ll EEE = 0, OOE = 0;
    for (int i = 0; i < n; i++) {
        ll cnt[64]{};
        for (int j = 0; j < n; j++) if (j != i) {
            int dx = (v[j].first - v[i].first);
            int dy = (v[j].second - v[i].second);
            int x = dx & 3;
            int y = dy & 3;
            int g = abs(__gcd(dx, dy)) & 3;
            ++cnt[x << 4 | y << 2 | g];
        }

        for (int m1 = 0; m1 < 64; m1++) {
            int x1 = m1 >> 4 & 3;
            int y1 = m1 >> 2 & 3;
            int g1 = m1 & 3;
            for (int m2 = m1; m2 < 64; m2++) {
                int x2 = m2 >> 4 & 3;
                int y2 = m2 >> 2 & 3;
                int g2 = m2 & 3;
                if (x1 + x2 & 1 || y1 + y2 & 1) continue;
                int g3 = (x2 == x1 && y2 == y1) ? 0 : 2;
                int B = g1 + g2 + g3 & 3;
                int S2 = x1 * y2 - y1 * x2 & 3;
                if (S2 & 1 || S2 != B) continue;

                ll add = (m1 == m2) ? cnt[m1] * (cnt[m1] - 1) / 2 : cnt[m1] * cnt[m2];
                ((x1 & 1 || y1 & 1) ? OOE : EEE) += add;
            }
        }
    }

    cout << EEE / 3 + OOE;
    return 0;
}
