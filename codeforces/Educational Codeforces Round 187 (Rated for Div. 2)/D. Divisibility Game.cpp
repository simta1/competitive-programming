#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<int> a(n), b(m);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        vector<bool> v(n + m + 1);
        for (auto e : a) v[e] = 1;
        for (int i = 1; i <= n + m; i++) if (v[i]) {
            for (int j = i; j <= n + m; j += i) v[j] = 1;
        }

        ll lcm = a[0];
        for (auto e : a) {
            lcm = lcm / __gcd(lcm, ll(e)) * e;
            if (lcm > n + m) break;
        }

        int acnt = 0, bcnt = 0, abcnt = 0;
        for (auto e : b) {
            if (v[e] && e % lcm) ++abcnt;
            else if (v[e]) ++acnt;
            else if (e % lcm) ++bcnt;
        }

        if ([&]() -> bool {
            for (int i = 0; i < m; i++) {
                if (i & 1) {
                    if (abcnt) --abcnt;
                    else if (bcnt) --bcnt;
                    else return true;
                }
                else {
                    if (abcnt) --abcnt;
                    else if (acnt) --acnt;
                    else return false;
                }
            }
            return m & 1;
        }()) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
