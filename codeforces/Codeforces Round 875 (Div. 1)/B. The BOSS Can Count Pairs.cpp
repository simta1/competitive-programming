#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<pair<ll, ll>> v(n);
        for (int i = 0; i < n; i++) cin >> v[i].first;
        for (int i = 0; i < n; i++) cin >> v[i].second;
        sort(v.begin(), v.end());

        // auto count = [&](const pair<ll, ll> &x) {
        //     return upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
        // };

        int sq = sqrt(2 * n);
        while (ll(sq) * sq > 2 * n) --sq;
        while (ll(sq + 1) * (sq + 1) <= 2 * n) ++sq;

        ll big = 0, small = 0;
        for (int A = 1; A <= sq; A++) {
            vector<int> cnt(n + 1);
            for (auto [a, b] : v) if (a == A) ++cnt[b];
            for (auto [a, b] : v) {
                ll B = ll(A) * a - b;
                ll &res = a <= sq ? small : big;
                if (B >= 1 && B <= n) res += cnt[B] - (a == A && b == B);
            }
        }

        cout << big + small / 2 << "\n";
    }

    return 0;
}
