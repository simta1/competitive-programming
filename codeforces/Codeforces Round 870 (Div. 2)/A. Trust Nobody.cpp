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

        auto check = [&](int x) {
            int cnt = 0;
            for (auto e : v) if (e > x) ++cnt;
            return cnt == x;
        };

        int ans = -1;
        for (int i = 0; i <= n; i++) {
            if (check(i)) {
                ans = i;
                break;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
