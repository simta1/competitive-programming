#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll l, r, g;
        cin >> l >> r >> g;
        if (r / g == (l - 1) / g) {
            cout << "-1 -1\n";
            continue;
        }

        ll x = (l - 1) / g + 1;
        ll y = r / g;
        ll mx = -1;
        ll A = -1, B = -1;
        for (ll a = x; a <= min(y, x + 2000); a++) {
            if (y - a <= mx) break;
            ll b = y;
            while (b >= a && __gcd(a, b) != 1) --b;
            if (b == a - 1) continue;
            if (mx < b - a) {
                mx = b - a;
                A = g * a;
                B = g * b;
            }
        }
        cout << A << " " << B << "\n";
    }

    return 0;
}
