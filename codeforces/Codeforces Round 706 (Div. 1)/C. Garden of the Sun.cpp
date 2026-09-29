#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<string> v(n);
        for (auto &st : v) cin >> st;

        if (m == 1) {
            for (int i = 0; i < n; i++) cout << "X\n";
            continue;
        }

        for (auto &st : v) {
            for (int j = 1; j < m; j += 3) st[j] = 'X';
        }

        for (int j = 2; j + 2 < m; j += 3) {
            int i = 0;
            while (i < n && v[i][j] == '.' && v[i][j + 1] == '.') ++i;
            if (i == n) i = 0;
            v[i][j] = v[i][j + 1] = 'X';
        }

        if ((m - 1) % 3 == 0) {
            for (int i = 0; i < n; i++) {
                if (v[i][m - 1] == 'X') v[i][m - 2] = 'X';
            }
        }

        for (auto &st : v) cout << st << "\n";
    }

    return 0;
}
