#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 2e5;
    static int pfs[N + 1];

    int TC;
    for (cin >> TC; TC--;) {
        int n, y;
        cin >> n >> y;

        memset(pfs, 0, sizeof(pfs));
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            ++pfs[x];
        }

        for (int i = 1; i <= N; i++) pfs[i] += pfs[i - 1];

        auto f = [&](int x) {
            ll res = 0;
            for (int c = 1; c <= (N - 1) / x + 1; c++) {
                int cnt = pfs[min(N, c * x)] - pfs[(c - 1) * x];
                res += cnt * ll(c);
                res -= max(0, cnt - pfs[c] + pfs[c - 1]) * ll(y);
            }
            return res;
        };

        ll ans = f(2);
        for (int x = 3; x <= N; x++) ans = max(ans, f(x));
        cout << ans << "\n";
    }

    return 0;
}
