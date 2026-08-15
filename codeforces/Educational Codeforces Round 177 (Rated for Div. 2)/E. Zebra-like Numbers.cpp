#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<tuple<ll, ll, ll>, ll> dp;
vector<ll> v = {1};
ll f(ll n, ll k, int idx) {
    if (idx == -1) return k == 0;

    if (dp.count({n, k, idx})) return dp[{n, k, idx}];
    auto &res = dp[{n, k, idx}];

    ll a = v[idx];
    if (n < a) return res = f(n, k, idx - 1);

    for (int i = 0; i < n / a; i++) if (k >= i) res += f(a - 1, k - i, idx - 1);
    res += f(n % a, k - n / a, idx - 1);
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    while (v.back() * 4 + 1 <= 1e18) v.push_back(v.back() * 4 + 1);
    // for (auto &e : v) cout << e << "\n";

    int TC;
    for (cin >> TC; TC--;) {
        ll l, r, k;
        cin >> l >> r >> k;
        cout << f(r, k, v.size() - 1) - f(l - 1, k, v.size() - 1) << "\n";
    }

    return 0;
}
