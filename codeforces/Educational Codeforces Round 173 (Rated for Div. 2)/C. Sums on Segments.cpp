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

        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (abs(v[i]) != 1) idx = i;
        }

        auto f = [&](int s, int e, int d) {
            int tmn = 0, tmx = 0;
            int cmn = 0, cmx = 0;
            if (d > 0) {
                for (int i = s; i <= e; i++) {
                    cmn = min(cmn + v[i], v[i]);
                    cmx = max(cmx + v[i], v[i]);
                    tmn = min(tmn, cmn);
                    tmx = max(tmx, cmx);
                }
            }
            else {
                for (int i = e; i >= s; i--) {
                    cmn = min(cmn + v[i], v[i]);
                    cmx = max(cmx + v[i], v[i]);
                    tmn = min(tmn, cmn);
                    tmx = max(tmx, cmx);
                }
            }
            return array{tmn, tmx, cmn, cmx};
        };

        constexpr int INF = 2e9;
        if (!~idx) {
            auto [a, b, c, d] = f(0, n - 1, 1);
            cout << b - a + 1 << "\n";
            for (int i = a; i <= b; i++) cout << i << " ";
            cout << "\n";
        }
        else {
            // cout << v[idx] << ":\n";
            auto [a, b, c, d] = f(0, idx - 1, 1);
            auto [a2, b2, c2, d2] = f(idx + 1, n - 1, -1);
            int mn = min(a, a2);
            int mx = max(b, b2);
            vector<int> ans1(mx - mn + 1);
            iota(ans1.begin(), ans1.end(), mn);

            // cout << a << " " << b << " " << c << " " << d << "\n";
            // cout << a2 << " " << b2 << " " << c2 << " " << d2 << "\n";
            int mn2 = v[idx] + min(c, 0) + min(c2, 0);
            int mx2 = v[idx] + max(d, 0) + max(d2, 0);
            // cout << v[idx] << "::\n";
            // cout << mn2 << " " << mx2 << "::\n";
            vector<int> ans2(mx2 - mn2 + 1);
            iota(ans2.begin(), ans2.end(), mn2);

            vector<int> ans;
            merge(ans1.begin(), ans1.end(), ans2.begin(), ans2.end(), back_inserter(ans));
            ans.erase(unique(ans.begin(), ans.end()), ans.end());
            cout << ans.size() << "\n";
            for (auto &e : ans) cout << e << " ";
            cout << "\n";
        }
    }

    return 0;
}
