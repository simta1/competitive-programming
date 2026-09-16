#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 2e5;
    constexpr ll MOD = 1e9 + 7;
    static ll fac[N + 1] = {1, 1};
    for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        ll ans = 0;
        for (auto bn : {a[n - 2], a[n - 1]}) {
            vector<int> path = {a[n], 0, bn};
            while (path.size() < n) {
                if (path.size() & 1) path.push_back(a[n] - path.back());
                else path.push_back(bn - path.back());
            }
            sort(path.begin(), path.end());
            bool same = 1;
            for (int i = 1; i <= n; i++) if (a[i] != path[i - 1]) same = 0;

            if (same) {
                int lo = n - 3 + 1 >> 1;
                int hi = n - 3 >> 1;
                ans += fac[lo + 1] * fac[hi];
                ans %= MOD;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
