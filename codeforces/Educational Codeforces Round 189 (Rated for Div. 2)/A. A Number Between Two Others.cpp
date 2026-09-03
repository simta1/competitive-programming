#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll x, y;
        cin >> x >> y;

        ll a = y / x;
        ll z = x * (a - 1);
        if (x < z && z < y) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
