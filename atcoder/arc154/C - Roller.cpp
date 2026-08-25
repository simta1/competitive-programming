#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n), b(n);
        for (auto &e : a) cin >> e;
        for (auto &e : b) cin >> e;

        auto check = [&](const vector<int> &v) {
            // for (auto &e : v) cout << e << " "; cout << "\n";
            int idx = 0;
            for (auto e : v) {
                while (idx < n && a[idx] != e) ++idx;
                if (idx == n) return false;
                ++idx;
            }
            return true;
        };

        if ([&]() {
            bool x = a[0] == a.back(), y = b[0] == b.back();
            for (int i = 1; i < n; i++) {
                if (a[i] == a[i - 1]) x = 1;
                if (b[i] == b[i - 1]) y = 1;
            }

            if (!x) {
                if (a == b) return true;
                if (!y) return false;
            }

            vector<int> v;
            for (int i = 0, j = 0; i < n; i = j) {
                while (j < n && b[i] == b[j]) ++j;
                v.push_back(b[i]);
            }

            if (v.size() >= 2 && v[0] == v.back()) v.pop_back();

            for (int _ = v.size(); _--;) {
                rotate(v.begin(), v.begin() + 1, v.end());
                if (check(v)) return true;
            }

            return false;
        }()) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
