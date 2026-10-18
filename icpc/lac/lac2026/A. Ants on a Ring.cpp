#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, l;
    cin >> n >> l;

    vector<pair<int, int>> v(n);
    for (auto &[a, b] : v) cin >> a;
    for (auto &[a, b] : v) cin >> b;
    sort(v.begin(), v.end());

    int b1 = v[0].second;
    for (auto &[a, b] : v) if (b < b1) b += l;

    for (int i = 1; i < n; i++) {
        if (v[i - 1].second > v[i].second) {
            cout << "*";
            return 0;
        }
    }

    ll ans = 9e18;
    for (ll k = -1; k < 2; k++) {
        ll mx = 0;
        for (auto &[a, b] : v) {
            mx = max(mx, abs(b - a + k * l));
        }
        ans = min(ans, mx);
    }
    cout << ans;

    return 0;
}
