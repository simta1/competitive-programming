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

        bool same = 1;
        for (int i = 1; i < n; i++) {
            if (v[i] != v[0]) same = 0;
        }

        if (same) {
            cout << "-1\n";
            continue;
        }

        if (v[0] != v.back()) {
            cout << "0\n";
            continue;
        }

        int i = 0;
        while (v[i] == v.back()) ++i;
        int ans = i;

        i = 0;
        while (v[v.size() - 1 - i] == v[0]) ++i;
        ans = min(ans, i);

        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            int len = j - i;
            if (v[i] != v[0]) {
                if (len > 1) ans = 0;
            }
            else {
                ans = min(ans, len);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
