#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        sort(v.begin(), v.end());

        ll prv = 0;
        ll ans = 0;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            ll cnt = j - i;
            if (cnt >= 3) ans += cnt * (cnt - 1) * (cnt - 2) / 6;
            if (cnt >= 2) ans += cnt * (cnt - 1) / 2 * prv;
            prv += cnt;
        }
        cout << ans << "\n";
    }

    return 0;
}
