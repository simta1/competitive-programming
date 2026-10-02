#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll a, b, c, m;
        cin >> a >> b >> c >> m;

        auto f = [&](ll a, ll b, ll c) {
            ll ab = a / __gcd(a, b) * b;
            ll ac = a / __gcd(a, c) * c;
            ll abc = ab / __gcd(ab, ac) * ac;
            ll x = m / a;
            ll y = m / ab;
            ll z = m / ac;
            ll w = m / abc;
            return w * 2 + (y - w) * 3 + (z - w) * 3 + (x - y - z + w) * 6;
        };

        cout << f(a, b, c) << " " << f(b, c, a) << " " << f(c, a, b) << "\n";
    }

    return 0;
}
