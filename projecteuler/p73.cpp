#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int MX = 12000;

    int ans = 0;
    auto dfs = [&](auto &&dfs, int a, int b, int c, int d) -> void {
        int x = a + c, y = b + d;
        if (y <= MX) {
            ++ans;
            dfs(dfs, a, b, x, y);
            dfs(dfs, x, y, c, d);
        }
    };
    dfs(dfs, 1, 3, 1, 2);

    cout << ans;

    return 0;
}
