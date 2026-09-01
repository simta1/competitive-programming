#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int c1 = 0, c2 = 0;
        vector<int> v(n);
        int mx = 0;
        for (auto &e : v) {
            cin >> e;
            mx = max(mx, e);
            if (e == 1) ++c1;
            else ++c2;
        }

        ll ans = [&]() -> ll {
            if (c2 == 0) return 0;
            if (c2 == 1) {
                // if (mx == 2) return mx + min(1, c1);
                return min(c1, mx / 2) + mx;
            }

            ll sum = 0, cnt = 0;
            for (auto e : v) {
                if (e >= 2) {
                    sum += e;
                    cnt += max(0, e / 2 - 1);
                }
            }
            return min<ll>(c1, cnt) + sum;

        }();
        if (ans < 3) ans = 0;
        cout << ans << "\n";
    }

    return 0;
}
