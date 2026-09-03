#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector v(n, vector<int>(n));
        for (auto &r : v) for (auto &e : r) cin >> e;

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cnt += v[i][j] != v[n - 1 - i][n - 1 - j];
            }
        }
        cnt /= 2;

        if ([&]() -> bool {
            if (k < cnt) return false;
            if (k + cnt & 1) {
                return n & 1;
            }
            else return true;
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
