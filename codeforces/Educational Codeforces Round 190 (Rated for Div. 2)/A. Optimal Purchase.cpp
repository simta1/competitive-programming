#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll n, a, b;
        cin >> n >> a >> b;
        if (3 * a <= b) cout << a * n << "\n";
        else {
            ll ans = n / 3 * b;
            if (n % 3 == 2) {
                ans += min(2 * a, b);
            }
            else if (n % 3 == 1) {
                ans += min(a, b);

            }
            cout << ans << "\n";
        }
    }

    return 0;
}
