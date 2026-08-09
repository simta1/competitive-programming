#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;

        vector<int> a(x), b(y);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        auto f = [&](int n1, int n2) {
            // cout << n1 << " " << n2 << "::\n";
            int mx1 = min<int>(n1, a.size());
            int mx2 = min<int>(n2, b.size());
            vector<int> v, v2;
            merge(a.begin(), a.begin() + mx1, b.begin(), b.begin() + mx2, back_inserter(v), greater<int>());
            merge(a.begin() + mx1, a.end(), b.begin() + mx2, b.end(), back_inserter(v2), greater<int>());
            // for (auto &e : v) cout << e << " "; cout << "\n";
            // for (auto &e : v2) cout << e << " "; cout << "\n";
            v.erase(unique(v.begin(), v.end()), v.end());
            v2.erase(unique(v2.begin(), v2.end()), v2.end());
            // for (auto &e : v) cout << e << " "; cout << "\n";
            // for (auto &e : v2) cout << e << " "; cout << "\n";
            ll sum = accumulate(v.begin(), v.end(), 0LL);
            int rem = min<int>(mx1 + mx2 - v.size(), v2.size());
            for (int i = 0; i < v2.size() && rem > 0; i++) {
                if (upper_bound(v.begin(), v.end(), v2[i], greater<int>()) - lower_bound(v.begin(), v.end(), v2[i], greater<int>())) continue;
                --rem;
                sum += v2[i];
            }
            // cout << rem << "::\n";
            // cout << n1 << " " << n2 << " " << sum << "::\n";
            return sum;
        };

        cout << max(f(n - 1, m), f(n, m - 1)) << "\n";
    }

    return 0;
}
