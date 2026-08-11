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
        const int full = (1 << 30) - 1;
        int sum = full;
        for (auto &e : v) {
            cin >> e;
            sum &= e;
        }

        if (sum) {
            cout << "1\n";
            continue;
        }

        int cur = full;
        int ans = 0;
        for (auto e : v) {
            cur &= e;
            if (!cur) {
                ++ans;
                cur = full;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
