#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        vector a(n, vector<int>(m));
        for (auto &r : a) for (auto &e : r) cin >> e;

        int ans = m;
        multiset<int> s;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < m; j++) s.insert(-a[i][j]);
            int cnt = 0;
            ll sum = 0;
            for (auto e : s) {
                if (sum >= v[i]) break;
                if (cnt >= ans) break;
                sum -= e;
                ++cnt;
            }
            ans = min(ans, cnt);
        }
        cout << ans << "\n";
    }

    return 0;
}
