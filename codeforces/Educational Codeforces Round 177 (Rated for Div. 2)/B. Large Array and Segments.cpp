#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll n, k, x;
        cin >> n >> k >> x;
        vector<ll> v(n);
        for (auto &e : v) cin >> e;
        for (int i = 1; i < n; i++) v[i] += v[i - 1];

        auto f = [&](ll l, ll r) {
            if (l <= r % n) {
                return v[r % n] - (l ? v[l - 1] : 0LL) + r / n * v.back();
            }
            else {
                return v[r % n] + v.back() - (l ? v[l - 1] : 0LL) + (r / n - 1) * v.back();
            }
        };
        ll ans = 0;
        for (int l = 0; l < n; l++) {
            ll lo = l - 1, hi = n * k;
            while (lo + 1 < hi) {
                ll mid = lo + hi >> 1;
                if (f(l, mid) >= x) hi= mid;
                else lo = mid;
            }
            // if (hi < n * k) ++ans;
            // cout << l << " " << hi << "\n";
            ll cnt = n * k - hi;
            if (cnt) {
                ll mx = (cnt - 1) / n;
                ans += mx + 1;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
