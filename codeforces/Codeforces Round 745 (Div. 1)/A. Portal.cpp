#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector v(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            string st;
            cin >> st;
            for (int j = 1; j <= m; j++) v[i][j] = st[j - 1] - '0';
        }

        auto pfs = v;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                pfs[i][j] += pfs[i][j - 1] + pfs[i - 1][j] - pfs[i - 1][j - 1];
            }
        }

        vector r(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) r[i][j] = r[i][j - 1] + !v[i][j];
        }

        vector c(m + 1, vector<int>(n + 1));
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                c[j][i] = c[j][i - 1] + !v[i][j];
            }
        }

        int ans = n * m;
        for (int i1 = 1; i1 <= n; i1++) {
            for (int i2 = i1 + 4; i2 <= n; i2++) {
                // for (auto &e : r[i1]) cout << e << " "; cout << "\n";
                // for (auto &e : r[i2]) cout << e << " "; cout << "\n";
                int mn = - r[i1][1] - r[i2][1] - (pfs[i2 - 1][1] - pfs[i1][1]) + (c[1][i2 - 1] - c[1][i1]);
                for (int j2 = 4; j2 <= m; j2++) {
                    int cur = r[i1][j2 - 1] + r[i2][j2 - 1] + (pfs[i2 - 1][j2 - 1] - pfs[i1][j2 - 1]) + (c[j2][i2 - 1] - c[j2][i1]);
                    // cout << r[i1][j2 - 1] + r[i2][j2 - 1] - - r[i1][1] - r[i2][1] << "::\n";
                    // cout << (c[1][i2 - 1] - c[1][i1]) + (c[j2][i2 - 1] - c[j2][i1]) << "::\n";
                    // cout << (pfs[i2 - 1][1] - pfs[i1][1]) << "::\n";
                    // cout << (pfs[i2 - 1][j2 - 1] - pfs[i1][j2 - 1]) << "::\n";
                    // cout << cur + mn << "::\n";
                    ans = min(ans, cur + mn);
                    mn = min(mn, - r[i1][j2 - 2] - r[i2][j2 - 2] - (pfs[i2 - 1][j2 - 2] - pfs[i1][j2 - 2]) + (c[j2 - 2][i2 - 1] - c[j2 - 2][i1]));
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
