#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, x, y, z;
        cin >> n >> x >> y >> z;
        int ans = (n + x + y - 1) / (x + y);
        // zx + (10y+x)(t-z) >= n
        int a = 10 * y + x;
        if (n >= z * x) {
            ans = min(ans, z + (n - z * x + a - 1) / a);
        }
        cout << ans << "\n";
    }

    return 0;
}
