#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    constexpr int INF = 2e9;
    auto getW = [&](int l, int r) {
        int x1 = INF, y1 = INF, x2 = -INF, y2 = -INF;
        int res = 0;
        for (int i = l; i <= r; i++) {
            auto [x, y] = v[i];
            x1 = min(x1, x);
            x2 = max(x2, x);
            y1 = min(y1, y);
            y2 = max(y2, y);
        }
        for (int i = l; i <= r; i++) {
            auto [x, y] = v[i];
            res = max(res, min({x - x1, x2 - x, y - y1, y2 - y}));
        }
        return res;
    };

    auto f = [&](int lcnt) {
        return max(getW(0, lcnt - 1), getW(lcnt, n - 1));
    };

    auto solve = [&]() {
        int lo = -1, hi = n + 1;
        while (lo + 1 < hi) {
            int mid = lo + hi >> 1;
            int a = getW(0, mid - 1);
            int b = getW(mid, n - 1);
            if (a <= b) lo = mid;
            else hi = mid;
        }
        int res = INF;
        if (lo >= 0) res = min(res, f(lo));
        if (hi <= n) res = min(res, f(hi));
        return res;
    };

    sort(v.begin(), v.end());
    int ans = solve();

    sort(v.begin(), v.end(), [&](auto a, auto b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    ans = min(ans, solve());

    int x1 = INF, y1 = INF, x2 = -INF, y2 = -INF;
    for (int i = 0; i < n; i++) {
        auto [x, y] = v[i];
        x1 = min(x1, x);
        x2 = max(x2, x);
        y1 = min(y1, y);
        y2 = max(y2, y);
    }
    auto getD = [&](auto a) {
        auto [x, y] = a;
        return min({x - x1, x2 - x, y - y1, y2 - y});
    };
    sort(v.begin(), v.end(), [&](auto a, auto b) {
        return getD(a) < getD(b);
    });

    cout << min(ans, solve());

    return 0;
}
