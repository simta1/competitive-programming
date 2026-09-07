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

        vector<int> pfs(n);
        pfs[1] = -(v[1] - v[0]) + 1;
        for (int i = 1; i + 1 < n; i++) {
            if (v[i + 1] - v[i] < v[i] - v[i - 1]) {
                pfs[i + 1] = -(v[i + 1] - v[i]) + 1;
            }
        }
        for (int i = 1; i < n; i++) pfs[i] += pfs[i - 1];

        vector<int> sfs(n);
        sfs[n - 2] = -(v[n - 1] - v[n - 2]) + 1;
        for (int i = 1; i + 1 < n; i++) {
            if (v[i] - v[i - 1] < v[i + 1] - v[i]) {
                sfs[i - 1] = -(v[i] - v[i - 1]) + 1;
            }
        }
        for (int i = n - 2; i >= 0; i--) sfs[i] += sfs[i + 1];

        // for (auto &e : sfs) cout << e << " "; cout << "\n";

        int q;
        for (cin >> q; q--;) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            if (x < y) {
                cout << v[y] - v[x] + (pfs[y] - pfs[x]) << "\n";
            }
            else {
                cout << v[x] - v[y] + (sfs[y] - sfs[x]) << "\n";
            }
        }
    }

    return 0;
}
