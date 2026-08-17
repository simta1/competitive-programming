#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];

        vector pfs(4, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            // cout << v[i] << " " << i << "\n";
            ++pfs[v[i]][i];
            pfs[1][i] += pfs[1][i - 1];
            pfs[2][i] += pfs[2][i - 1];
            pfs[3][i] += pfs[3][i - 1];
        }

        vector<int> a(n);
        for (int i = 1; i <= n - 1; i++) a[i] = pfs[1][i] + pfs[2][i] - pfs[3][i];
        auto sfmax = a;
        for (int i = n - 2; i >= 1; i--) sfmax[i] = max(sfmax[i], sfmax[i + 1]);
        // for (int i = 1; i < n; i++) {
        //     cout << a[i] << " ";
        // }
        // cout << "\n";

        if ([&]() {
            for (int i = 1; i + 2 <= n; i++) if (pfs[1][i] - pfs[2][i] - pfs[3][i] >= 0) {
                // cout << i << "::\n";
                if (sfmax[i + 1] >= a[i]) return true;
            }
            return false;
            
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
