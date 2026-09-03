#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr array<pair<int, int>, 4> dpos = {{
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
}};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        auto inRange = [&](int i, int j) {
            return i >= 1 && j >= 1 && i <= n && j <= m;
        };

        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int ans = 0;
        for (auto [di, dj] : dpos) {
            int ni = a + di;
            int nj = b + dj;
            if (inRange(ni, nj)) ++ans;
        }

        int ans2 = 0;
        for (auto [di, dj] : dpos) {
            int ni = c + di;
            int nj = d + dj;
            if (inRange(ni, nj)) ++ans2;
        }

        ans = min(ans, ans2);

        if (b != d) ans = min(ans, m);
        if (a != c) ans = min(ans, n);

        cout << ans << "\n";
    }

    return 0;
}
