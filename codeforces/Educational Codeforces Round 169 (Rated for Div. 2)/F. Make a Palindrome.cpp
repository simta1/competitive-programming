#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
            v[i] += v[i - 1];
        }

        map<int, int> mp;
        ll ans = 0;
        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                ans += r - l;
                ++mp[v[l - 1] + v[r]];
            }
        }

        for (auto [sum, cnt] : mp) {
            ans -= cnt * (cnt - 1);
            if (~sum & 1 && binary_search(v.begin(), v.end(), sum >> 1)) ans -= cnt;
        }
        cout << ans << "\n";
    }

    return 0;
}
