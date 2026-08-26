#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector v(n, vector<int>(m));
        vector<int> cnt(n * m + 1);
        for (auto &r : v) for (auto &e : r) cin >> e, ++cnt[e];
        vector<bool> a(n * m + 1);
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (v[i][j - 1] == v[i][j]) a[v[i][j]] = 1;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (v[i - 1][j] == v[i][j]) a[v[i][j]] = 1;
            }
        }

        int sum = 0, mx = 0;
        for (int i = 1; i <= n * m; i++) if (cnt[i]) {
            int x = 1 + a[i];
            sum += x;
            mx = max(mx, x);
        }
        cout << sum - mx << "\n";
    }

    return 0;
}
