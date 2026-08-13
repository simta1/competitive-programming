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

        vector<int> pref(n), suf(n);
        for (int i = 0; i < n; i++) {
            pref[i] = v[i] + i;
            suf[i] = v[i] - i;
        }
        for (int i = 1; i < n; i++) pref[i] = max(pref[i], pref[i - 1]);
        for (int i = n - 2; i >= 0; i--) suf[i] = max(suf[i], suf[i + 1]);

        int ans = -1e9;
        for (int i = 1; i + 1 < n; i++) {
            ans = max(ans, suf[i + 1] + pref[i - 1] + v[i]);
        }
        cout << ans << "\n";
    }

    return 0;
}
