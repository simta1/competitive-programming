#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        string st;
        cin >> st;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        auto check = [&](int mx) {
            string cur;
            for (int i = 0; i < n; i++) {
                if (v[i] > mx) cur += st[i];
            }

            // cout << cur;
            int res = 0;
            for (int i = 0, j = 0; i < cur.size(); i = j) {
                while (j < cur.size() && cur[i] == cur[j]) ++j;
                if (cur[i] == 'B') ++res;
            }
            return res <= k;
        };

        // check(10);
        int lo = -1, hi = 1e9;
        while (lo + 1 < hi) {
            int mid = lo + hi >> 1;
            if (check(mid)) hi = mid;
            else lo = mid;
        }
        cout << hi << "\n";
    }

    return 0;
}
