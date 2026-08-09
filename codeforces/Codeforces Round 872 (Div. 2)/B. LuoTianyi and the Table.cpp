#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll n, m;
        cin >> n >> m;

        vector<ll> v(n * m);
        for (auto &e : v) cin >> e;
        sort(v.begin(), v.end());

        ll mn = v[0], mn2 = v[1], mx = v.back(), mx2 = v[v.size() - 2];
        ll ans = max({
            (n * m - 1) * mx - n * (m - 1) * mn - (n - 1) * mn2,
            (n * m - 1) * mx - n * (m - 1) * mn2 - (n - 1) * mn,
            -(n * m - 1) * mn + n * (m - 1) * mx + (n - 1) * mx2,
            -(n * m - 1) * mn + n * (m - 1) * mx2 + (n - 1) * mx,
        });
        swap(n, m);
        ll ans2 = max({
            (n * m - 1) * mx - n * (m - 1) * mn - (n - 1) * mn2,
            (n * m - 1) * mx - n * (m - 1) * mn2 - (n - 1) * mn,
            -(n * m - 1) * mn + n * (m - 1) * mx + (n - 1) * mx2,
            -(n * m - 1) * mn + n * (m - 1) * mx2 + (n - 1) * mx,
        });
        cout << max(ans, ans2) << "\n";

    }

    return 0;
}
