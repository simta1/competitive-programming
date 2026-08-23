#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, x;
        ll k;
        cin >> n >> x >> k;

        string st;
        cin >> st;

        ll ans = 0;
        for (auto ch : st) {
            if (ch == 'L') {
                --x;
            }
            else {
                ++x;
            }
            --k;
            if (!x) {
                ++ans;
                break;
            }
        }

        if (x == 0) {
            int cur = 0;
            int idx = -1;
            for (int i = 0; i < n; i++) {
                if (st[i] == 'L') --cur;
                else ++cur;
                if (!cur) {
                    idx = i;
                    break;
                }
            }

            if (~idx) ans += k / (idx + 1);
        }
        cout << ans << "\n";

    }

    return 0;
}
