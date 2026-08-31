#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n), b(n + 1);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        int t = b.back();
        ll x = 9e18;;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) swap(a[i], b[i]);
            ans += b[i] - a[i];
            if (t < a[i]) x = min<ll>(x, a[i] - t);
            else if (t <= b[i]) x = 0;
            else x = min<ll>(x, t - b[i]);
        }
        cout << ans + x + 1 << "\n";
    }

    return 0;
}
