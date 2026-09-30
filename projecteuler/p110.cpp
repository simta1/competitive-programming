#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    // n(x+y) = xy
    // (x-n)(y-n)=n^2

    int primes[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    ll ans = 9e18;
    auto dfs = [&](auto &&dfs, int idx, int mxe, ll cur, ll tau) {
        if (idx == 15) {
            if (tau > 7'999'999) ans = min(ans, cur);
            return;
        }
        int p = primes[idx];
        for (int e = 0; e <= mxe && cur < ans; ++e, cur *= p) {
            dfs(dfs, idx + 1, e, cur, tau * (2 * e + 1));
        }
    };
    dfs(dfs, 0, 100, 1, 1);
    cout << ans;

    return 0;
}
