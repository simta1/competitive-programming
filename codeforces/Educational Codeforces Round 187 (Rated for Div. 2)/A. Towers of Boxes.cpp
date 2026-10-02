#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m, d;
        cin >> n >> m >> d;

        int ans = 1, cur = 0;
        for (int i = 1; i < n; i++) {
            if (cur + m <= d) {
                cur += m;
            }
            else {
                cur = 0;
                ++ans;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
