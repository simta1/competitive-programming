#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    cout << fixed << setprecision(12);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<ll> a, b;
        for (int _ = 2 * n; _--;) {
            ll x, y;
            cin >> x >> y;
            if (x == 0) a.push_back(y * y);
            else b.push_back(x * x);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        using ld = double;
        ld ans = 0;
        for (int i = 0; i < n; i++) {
            ans += sqrt(a[i] + b[i]);
        }
        cout << ans << "\n";
    }

    return 0;
}
