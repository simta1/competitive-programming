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

        int ans = 0;
        vector<pair<int, int> > a;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            a.emplace_back(v[i], j - i);
            ++ans;
        }

        int mx = 0;
        for (int i = 1; i < a.size(); i++) {
            if (a[i].second > 1 && a[i - 1].second > 1) {
                mx = max(mx, 2);
            }
            else if (a[i].second > 1) {
                if (i - 2 < 0 || a[i].first != a[i - 2].first) mx = max(mx, 1);
            }
            else if (a[i - 1].second > 1) {
                if (i + 1 == a.size() || a[i + 1].first != a[i - 1].first) mx = max(mx, 1);
            }
        }
        cout << ans + mx << "\n";
    }

    return 0;
}
