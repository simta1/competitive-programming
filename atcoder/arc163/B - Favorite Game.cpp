#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int a1, a2;
    cin >> a1 >> a2;

    vector<int> v(n - 2);
    for (auto &e : v) cin >> e;
    n -= 2;

    sort(v.begin(), v.end());
    ll ans = 9e18;
    for (int i = 0; i + m - 1 < n; i++) {
        // a1 <= v[i]일 때
        // a2 >= v[i + m - 1]
        ll need = max(0, a1 - v[i]) + max(0, v[i + m - 1] - a2);
        ans = min(ans, need);
    }

    // a[1] = a1일 때는
    int idx = lower_bound(v.begin(), v.end(), a1) - v.begin();
    if (idx + m - 1 < n) {
        ans = min(ans, max<ll>(0, v[idx + m - 1] - a2));
    }
    cout << ans << "\n";

    return 0;
}
