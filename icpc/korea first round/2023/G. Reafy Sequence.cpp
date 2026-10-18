#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> res;
    auto dfs = [&](auto &&dfs, int a, int b, int c, int d) -> void {
        int x = a + c, y = b + d;
        if (y <= n) {
            dfs(dfs, a, b, x, y);
            res.emplace_back(x, y);
            dfs(dfs, x, y, c, d);
        }
    };
    res.emplace_back(0, 1);
    dfs(dfs, 0, 1, 1, 1);
    res.emplace_back(1, 1);

    cout << res[k - 1].first << " " << res[k - 1].second << "\n";

    return 0;
}
