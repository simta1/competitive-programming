#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> ds(int n) {
    vector<ll> res;
    for (ll a = 1, i = 0; i <= 2 * n; ++i, a *= 2) {
        for (ll b = 1, j = 0; j <= 2 * n; ++j, b *= 5) {
            res.push_back(a * b);
        }
    }
    return res;
}

int tau(int n) {
    int res = 0;
    for (int d = 1; d <= n / d; d++) if (n % d == 0) {
        ++res;
        res += (d != n / d) ;
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    ll ans = 0;
    for (ll pw = 10, n = 1; n <= 9; ++n, pw *= 10) {
        for (auto d : ds(n)) if (d <= pw) {
            ll a = d + pw;
            ll b = pw * pw / d + pw;
            ans += tau(__gcd(a, b));
        }
    }
    cout << ans;

    return 0;
}
