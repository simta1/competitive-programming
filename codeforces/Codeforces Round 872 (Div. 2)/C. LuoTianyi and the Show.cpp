#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<int> xs;
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (x == -1) ++l;
            else if (x == -2) ++r;
            else xs.push_back(x);
        }

        // cout << l << " " << r << "::\n";
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        int ans = 0;
        auto f = [&](int s, int e) {
            int res = e - s + 1;
            res += lower_bound(xs.begin(), xs.end(), s) - xs.begin();
            // if (s == 5 && e == 5) cout << res << "--\n";
            res += xs.end() - upper_bound(xs.begin(), xs.end(), e);
            // if (s == 5 && e == 5) cout << res << "--\n";
            ans = max(ans, res);
            // cout << s << " " << e << " " << res << "::\n";
        };

        for (auto idx : xs) {
            int lo = 0, hi = idx;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                int cnt = lower_bound(xs.begin(), xs.end(), idx) - lower_bound(xs.begin(), xs.end(), mid);
                if (cnt + l >= idx - mid) hi = mid;
                else lo = mid;
            }
            int s = hi;

            lo = idx, hi = m + 1;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                int cnt = upper_bound(xs.begin(), xs.end(), mid) - upper_bound(xs.begin(), xs.end(), idx);
                if (cnt + r >= mid - idx) lo = mid;
                else hi = mid;
            }
            int e = lo;
            f(s, e);
        }

        int idx = 0;
        int lo = idx, hi = m + 1;
        while (lo + 1 < hi) {
            int mid = lo + hi >> 1;
            int cnt = upper_bound(xs.begin(), xs.end(), mid) - upper_bound(xs.begin(), xs.end(), idx);
            if (cnt + r >= mid - idx) lo = mid;
            else hi = mid;
        }
        f(1, lo);

        idx = m + 1;
        lo = 0, hi = idx;
        while (lo + 1 < hi) {
            int mid = lo + hi >> 1;
            int cnt = lower_bound(xs.begin(), xs.end(), idx) - lower_bound(xs.begin(), xs.end(), mid);
            if (cnt + l >= idx - mid) hi = mid;
            else lo = mid;
        }
        f(hi, m);

        cout << ans << "\n";
    }

    return 0;
}
