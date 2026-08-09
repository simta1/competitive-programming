#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int x, y;
        cin >> x >> y;

        int k = (x + y) * 2;
        ll n = sqrt(k);
        while (n * (n + 1) > k) --n;
        while ((n + 1) * (n + 2) <= k) ++n;
        ll diff = x + y - n * (n + 1) / 2;
        ll dx = diff / 2;
        ll mn = max<ll>(diff - y, 0);
        ll mx = min<ll>(diff, x);
        if (dx < mn) dx = mn;
        if (dx > mx) dx = mx;
        ll dy = diff - dx;
        ll ex = x - dx;
        ll ey = y - ey;
        for (int i = n; i >= 1; i--) {
            if (ex >= i) {
                ex -= i;
                cout << "X";
            }
            else {
                ey -= i;
                cout << "Y";
            }
        }
        cout << "\n";
    }

    return 0;
}
