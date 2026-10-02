#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll s, m;
        cin >> s >> m;
        if (s % (m & -m)) cout << "-1\n";
        else {
            vector<ll> v;
            for (ll tmp = m; tmp; tmp &= tmp - 1) v.push_back(tmp & -tmp);
            reverse(v.begin(), v.end());

            auto check = [&](ll mid) {
                ll tmp = s;
                for (auto e : v) {
                    ll x = min(tmp / e, mid);
                    tmp -= x * e;
                }
                return tmp == 0;
            };

            ll lo = 0, hi = s;
            while (lo + 1 < hi) {
                ll mid = lo + hi >> 1;
                if (check(mid)) hi = mid;
                else lo = mid;
            }
            cout << hi << "\n";
        }
    }

    return 0;
}
