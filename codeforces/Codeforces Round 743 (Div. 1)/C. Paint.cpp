#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> idxes(n + 1);
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            idxes[v[i]].push_back(i);
        }

        constexpr int INF = 1e9;
        vector dp(n, vector<int>(n, -1));
        auto f = [&](auto &&f, int l, int r) -> int {
            if (l == r) return 0;
            if (l + 1 == r) return v[l] != v[r];

            auto &res = dp[l][r];
            if (~res) return res;

            res = f(f, l + 1, r) + 1;
            for (auto idx : idxes[v[l]]) if (idx > l) {
                if (idx > r) break;
                res = min(res, f(f, l, idx - 1) + f(f, idx, r));
            }
            return res;
        };
        cout << f(f, 0, n - 1) << "\n";
    }

    return 0;
}
