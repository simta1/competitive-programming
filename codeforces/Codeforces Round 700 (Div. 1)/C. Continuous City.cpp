#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(int i) {
    return 21 - i;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int l, r;
    cin >> l >> r;

    int tl = l, tr = r;

    int n = 22;
    vector<array<int, 3>> ans;

    vector<vector<pair<int, int>>> rdj(n + 1);
    vector<int> outdeg(n + 1);
    auto addEdge = [&](int u, int v, int w) {
        assert(u < v);
        ans.push_back({u, v, w});
        ++outdeg[u];
        rdj[v].emplace_back(u, w);
    };

    for (int i = 0; i < 20; i++) {
        addEdge(f(i), n, 1);
        for (int j = 0; j < i; j++) {
            addEdge(f(i), f(j), 1 << j);
        }
    }

    addEdge(1, n, l);
    for (int cur = r - l; cur; cur &= cur - 1) {
        int bit = cur & -cur;
        addEdge(1, f(__lg(bit)), r - bit);
        r -= bit;
    }

    constexpr int MX = 1048576;
    vector<bitset<MX>> dp(n + 1);
    queue<int> q;
    dp[n][0] = 1;
    for (int i = 1; i <= n; i++) if (outdeg[i] == 0) q.push(i);
    // cout << q.size() << "--\n";
    // cout << q.front() << "--\n";
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (auto [prv, w] : rdj[cur]) {
            dp[prv] |= dp[cur] << w;
            if (--outdeg[prv] == 0) q.push(prv);
        }
    }

    auto gdp = [&](int i) {
        const bitset<MX> &bs = dp[i];
        int mn = bs._Find_first();
        assert(mn != bs.size());
        int mx = mn + bs.count() - 1;
        assert(bs._Find_next(mx) == bs.size());
        return pair{mn, mx};
    };

    for (int i = 0; i < 20; i++) {
        auto [mn, mx] = gdp(f(i));
        // cout << i << " " << mn << " " << mx << "::\n";
        assert(mn == 1 && mx == (1 << i));
    }

    auto [mn, mx] = gdp(1);
    // cout << mn << " " << mx << "::\n";
    assert(mn == tl && mx == tr);

    cout << "YES\n";
    cout << n << " " << ans.size() << "\n";
    for (auto [a, b, c] : ans) cout << a << " " << b << " " << c << "\n";

    return 0;
}
