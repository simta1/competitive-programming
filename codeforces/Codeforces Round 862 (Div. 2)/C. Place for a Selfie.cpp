#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<ll> ks(n);
        for (auto &k : ks) cin >> k;
        sort(ks.begin(), ks.end());
        ks.erase(unique(ks.begin(), ks.end()), ks.end());

        while (m--) {
            ll a, b, c;
            cin >> a >> b >> c;

            int ans;
            if ([&]() {
                if (c <= 0) return false;

                ll x = ceil(2.0 * sqrt(ld(a * c))) + 2;
                auto i = lower_bound(ks.begin(), ks.end(), b - x);

                int cnt = 0;
                for (auto it = i; it != ks.end(); it++) {
                    if (++cnt == 7) break;
                    auto k = *it;
                    if ((b - k) * (b - k) - 4 * a * c < 0) {
                        ans = k;
                        return true;
                    }
                }
                return false;
            }()) {
                cout << "YES\n";
                cout << ans << "\n";
            }
            else cout << "NO\n";

        }
    }

    return 0;
}
