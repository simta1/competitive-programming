#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using hh = __int128;
int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string a, b;
    ll c, d;
    cin >> a >> b >> c >> d;

    int n = a.size();
    int m = b.size();
    set<pair<ll, array<int, 10>>> s;
    for (int mask = 0; mask < (1 << m); mask++) {
        array<int, 10> cnt{};
        ll b2 = 0;
        bool flag = 1;
        for (int i = 0; i < m; i++) {
            if (mask >> i & 1) {
                b2 = b2 * 10 + (b[i] - '0');
                if (b2 == 0) flag = 0;
            }
            else {
                ++cnt[b[i] - '0'];
            }
        }
        if (flag) s.emplace(b2, cnt);
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        array<int, 10> cnt{};
        ll a2 = 0;
        bool flag = 1;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                a2 = a2 * 10 + (a[i] - '0');
                if (a2 == 0) flag = 0;
            }
            else {
                ++cnt[a[i] - '0'];
            }
        }
        if (!flag || a2 == 0 || hh(a2) * d % c) continue;
        hh b2 = hh(a2) * d / c;
        if (b2 >= 1'000'000'000'000'000'000) continue;
        auto it = s.find(pair{ll(b2), cnt});
        if (it != s.end()) {
            cout << "possible\n";
            cout << a2 << " " << ll(b2) << "\n";
            return 0;
        }
    }

    cout << "impossible";
    return 0;
}
