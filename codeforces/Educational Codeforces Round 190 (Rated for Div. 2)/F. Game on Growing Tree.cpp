#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int get2(pair<int, int> mx[], int x) {
    int cnt = 0;
    for (int i = 0; i < 3; i++) if (mx[i].second != x) {
        if (++cnt == 2) return mx[i].first;
    }
    assert(false);
}

int f(const vector<vector<int>> &chd, int n) {
    vector<int> down(n + 1);
    auto dfs = [&](auto &&dfs, int cur) -> void {
        int mx = 0, mx2 = 0;
        for (auto nxt : chd[cur]) if (nxt <= n) {
            dfs(dfs, nxt);
            int val = down[nxt];
            if (mx < val) swap(mx, val);
            if (mx2 < val) swap(mx2, val);
        }
        down[cur] = mx2 + 1;
    };
    dfs(dfs, 1);

    int res = 0;

    vector<int> up(n + 1);
    auto dfs2 = [&](auto &&dfs2, int cur, int par) -> void {
        pair<int, int> mx[3]{};
        if (~par) mx[0] = {up[cur], par};
        for (auto nxt : chd[cur]) if (nxt <= n) {
            pair<int, int> val = {down[nxt], nxt};
            for (int i = 0; i < 3; i++) {
                if (mx[i] < val) swap(mx[i], val);
            }
        }

        res = max(res, mx[1].first + 1);
        for (auto nxt : chd[cur]) if (nxt <= n) {
            up[nxt] = get2(mx, nxt) + 1;
            dfs2(dfs2, nxt, cur);
        }
    };
    dfs2(dfs2, 1, -1);

    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;
    ++n;

    vector<vector<int>> chd(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        chd[p].push_back(i);
    }

    vector<int> ans(n + 1);
    auto dnc = [&](auto &&dnc, int s, int e, int lo, int hi) {
        if (s > e) return;
        if (lo == hi) {
            for (int i = s; i <= e; i++) ans[i] = lo;
            return;
        }
        int m = s + e >> 1;
        ans[m] = f(chd, m);
        dnc(dnc, s, m - 1, lo, ans[m]);
        dnc(dnc, m + 1, e, ans[m], hi);
    };
    dnc(dnc, 2, n, 1, 30);

    for (int i = 2; i <= n; i++) cout << ans[i] << " ";

    return 0;
}
