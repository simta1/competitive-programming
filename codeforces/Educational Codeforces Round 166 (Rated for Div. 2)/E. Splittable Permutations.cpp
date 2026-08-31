#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> l(q), r(q);
    for (auto &e : l) cin >> e;
    for (auto &e : r) cin >> e;

    vector<int> p(n + q + 1);
    iota(p.begin(), p.end(), 0);
    auto find = [&](int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    };

    vector<vector<int>> chd(n + q + 1);
    for (int i = q - 1; i >= 0; i--) {
        int x = ++n;
        int a = find(l[i]);
        int b = find(r[i]);
        chd[x].push_back(a);
        chd[x].push_back(b);
        p[a] = x;
        p[b] = x;
        // cout << x << " " << a << " " << b << "::\n";
    }

    n -= q;
    vector<int> v;
    vector<bool> used(n + 1);
    auto dfs = [&](auto &&dfs, int cur) -> void {
        if (cur <= n) {
            v.push_back(cur);
            used[cur] = 1;
        }
        if (cur >= chd.size()) {
            exit(0);
        }
        assert(cur < chd.size());
        for (auto nxt : chd[cur]) dfs(dfs, nxt);
    };
    dfs(dfs, n + q);

    // for (auto &e : v) cout << e << " "; cout << "\n";

    vector<int> cnt(n + 1);
    ++cnt[v[0] - 1];
    ++cnt[v.back() - 1];
    for (int i = 1; i < v.size(); i++) ++cnt[max(v[i - 1], v[i]) - 1];

    int cur = 0;
    ll ans = 1;
    constexpr ll MOD = 998'244'353;
    for (int val = n; val >= 1; val--) {
        cur += cnt[val];
        if (!used[val]) {
            // cout << val << " " << cur << "\n";
            ans = ans * cur % MOD;
            ++cur;
        }
    }
    cout << ans;

    return 0;
}
