#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    // cout << sqrt(2e5);
    constexpr int B = 440;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    vector<int> imos(m);
    static int b[B][B];
    int cur = 0;
    vector<int> last(n);
    for (int t = 0; t < m; t++) {
        int op, k;
        cin >> op >> k;
        --k;
        auto [x, y] = v[k];

        if (op == 1) {
            if (x + y >= B) {
                for (int l = t + x, r = t + x + y - 1; l < m; l += x + y, r += x + y) {
                    r = min(m - 1, r);
                    ++imos[l];
                    if (r + 1 < m) --imos[r + 1];
                }
            }
            else {
                for (int r = x; r < x + y; r++) ++b[x + y][(r + t) % (x + y)];
            }
            last[k] = t;
        }
        else {
            int s = last[k];
            if (x + y >= B) {
                for (int l = s + x, r = s + x + y - 1; l < m; l += x + y, r += x + y) {
                    r = min(m - 1, r);
                    int l2 = max(l, t);
                    if (l2 <= r) {
                        --imos[l2];
                        if (r + 1 < m) ++imos[r + 1];
                    }
                }
            }
            else {
                for (int r = x; r < x + y; r++) --b[x + y][(r + s) % (x + y)];
            }
        }

        cur += imos[t];
        int ans = cur;
        for (int i = 1; i < B; i++) ans += b[i][t % i];
        cout << ans << "\n";
    }

    return 0;
}
