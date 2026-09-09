#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<ll> v(n);
        for (auto &e : v) cin >> e;

        vector<pair<ll, int>> a = {{0, 0}};

        int ans = 1;
        for (int i = 1; i < n; i++) {
            vector<pair<ll, int>> na = {{0, i}};
            ll cur = abs(v[i] - v[i - 1]);
            for (auto [g, l] : a) {
                ll ng = __gcd(g, cur);
                if (ng == 1) continue;
                if (!na.empty() && na.back().first == ng) na.back().second = l;
                else na.emplace_back(ng, l);
                ans = max(ans, i - l + 1);
            }
            swap(na, a);
        }
        cout << ans << "\n";
    }

    return 0;
}
