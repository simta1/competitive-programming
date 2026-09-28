#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 5e5;

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        int g = 0;
        while (m--) {
            int b;
            cin >> b;
            g = __gcd(g, b);
        }

        ll ans[2]{};
        for (int i = 0; i < g; i++) {
            int cnt = 0, mn = 2e9;
            ll sum = 0;
            for (int j = i; j < n; j += g) {
                if (v[j] < 0) ++cnt;
                sum += abs(v[j]);
                mn = min(mn, abs(v[j]));
            }
            if (cnt & 1) {
                ans[0] += sum - 2 * mn;
                ans[1] += sum;
            }
            else {
                ans[0] += sum;
                ans[1] += sum - 2 * mn;
            }
        }

        cout << max(ans[0], ans[1]) << "\n";
    }

    return 0;
}
