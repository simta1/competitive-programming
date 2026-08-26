#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n), cnt(n + 1);
        for (auto &e : v) cin >> e, ++cnt[e];

        int one = 0, two = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 1) ++one;
            else if (cnt[i] > 1) ++two;
        }

        int ans = (one + 1 >> 1) * 2;
        ans += two;
        cout << ans << "\n";
        
    }

    return 0;
}
