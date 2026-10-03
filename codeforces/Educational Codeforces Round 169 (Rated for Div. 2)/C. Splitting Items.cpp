#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int t;
    for (cin >> t; t--;) {
        int n;
        ll k;
        cin >> n >> k;

        vector<ll> v(n);
        for (auto &e : v) cin >> e;
        sort(v.begin(), v.end());
        for (int i = n - 2; i >= 0; i -= 2) {
            ll inc = min(k, v[i + 1] - v[i]);
            v[i] += inc;
            k -= inc;
        }

        ll ans = 0;
        for (int i = n - 1, sign = 1; i >= 0; i--, sign *= -1) ans += v[i] * sign;
        cout << ans << "\n";
    }

    return 0;
}
