#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    static bool v[500][500][4];
    for (int i = 0; i < n; i++) {
        string st;
        cin >> st;
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                bool a = st[i] - '0';
                bool b = st[j] - '0';
                v[i][j][a << 1 | b] = 1;
            }
        }
    }

    while (q--) {
        string st;
        cin >> st;
        if ([&]() {
            for (int i = 0; i < m; i++) {
                for (int j = i; j < m; j++) {
                    bool a = st[i] - '0';
                    bool b = st[j] - '0';
                    if (!v[i][j][a << 1 | b]) return false;
                }
            }
            return true;
        }()) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
