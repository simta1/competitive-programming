#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        map<int, int> mp;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            ++mp[x];
            ans += x;
        }

        int mx = 0, v;
        for (auto [val, cnt] : mp) {
            if (mx < cnt) {
                mx = cnt;
                v = val;
            }
        }

        int half = n + 1 >> 1;
        if (mx > half) {
            // cout << mx << " " << v << "::\n";
            int a = n - mx;
            // cout << v * (mx - min(a + 1, mx)) << "::\n";
            ans -= v * (mx - min(a + 2, mx));
        }

        cout << ans << "\n";
    }

    return 0;
}
