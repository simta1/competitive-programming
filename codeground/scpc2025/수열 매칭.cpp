#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
void add(ll &a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

#define size(x) (int((x).size()))

struct Seg {
    int sz = 1;
    vector<int> tree, lazy;
    Seg(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1);
        lazy.resize(sz << 1);
    }
    void apply(int node, int s, int e, ll add) {
        tree[node] += add;
        if (s != e) lazy[node] += add;
    }
    void push(int node, int s, int e) {
        if (!lazy[node] || s == e) return;
        int m = s + e >> 1;
        apply(node << 1, s, m, lazy[node]);
        apply(node << 1 | 1, m + 1, e, lazy[node]);
        lazy[node] = 0;
    }
    void update(int node, int s, int e, int l, int r, ll add) {
        if (l <= s && e <= r) {
            apply(node, s, e, add);
            return;
        }
        if (l > e || s > r) return;
        push(node, s, e);
        int m = s + e >> 1;
        update(node << 1, s, m, l, r, add);
        update(node << 1 | 1, m + 1, e, l, r, add);
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++) {
        int n, k;
        cin >> n >> k;

        int cnt[5]{};
        vector<int> v(2 * n);
        for (auto &e : v) cin >> e, ++cnt[e];

        cout << "Case #" << tc << "\n";

        if (cnt[0]) {
            assert(k == 3);
            vector dp(n + 1, vector<array<ll, 2>>(n + 1));
            dp[0][0][0] = 1;
            for (auto e2 : v) {
                vector ndp(n + 1, vector<array<ll, 2>>(n + 1));
                vector<int> candi = e2 ? vector{e2} : vector{1, 2, 3};
                for (auto e : candi) {
                    if (e == 1) {
                        for (int a = 0; a < n; a++) {
                            for (int b = 0; b <= n; b++) {
                                for (int right = 0; right < 2; right++) {
                                    add(ndp[a + 1][b][right], dp[a][b][right]);
                                }
                            }
                        }
                    }
                    else if (e == 3) {
                        for (int a = 0; a <= n; a++) {
                            for (int b = 0; b <= n; b++) {
                                for (int right = 0; right < 2; right++) {
                                    if (b) add(ndp[a][b - 1][right], dp[a][b][right]);
                                    else if (a) add(ndp[a - 1][0][right], dp[a][0][right]);
                                }
                            }
                        }
                    }
                    else {
                        // right=0
                        for (int a = 0; a <= n; a++) {
                            for (int b = 0; b <= n; b++) {
                                if (b < n) add(ndp[a][b + 1][0], dp[a][b][0]);
                                if (a) add(ndp[a - 1][b][1], dp[a][b][0]);
                            }
                        }
                        // right=1
                        for (int a = 1; a <= n; a++) {
                            for (int b = 0; b <= n; b++) {
                                add(ndp[a - 1][b][1], dp[a][b][1]);
                            }
                        }
                    }
                }
                swap(dp, ndp);
            }
            ll ans = dp[0][0][0] + dp[0][0][1];
            if (ans >= MOD) ans -= MOD;
            cout << ans << "\n";
        }
        else if (k == 3) {
            int a = 0, b = 0;
            int left2 = n - cnt[1];
            bool ans = 1;
            for (auto e : v) {
                if (e == 1) ++a;
                else if (e == 2) {
                    if (left2 > 0) {
                        --left2;
                        ++b;
                    }
                    else --a;
                }
                else {
                    if (b) --b;
                    else --a;
                }
                if (a < 0) ans = 0;
            }
            if (a || b) ans = 0;
            cout << ans << "\n";
        }
        else {
            int need = n - cnt[1];
            vector<pair<int, int>> a, b;
            queue<int> tmp;
            for (int i = 2 * n - 1; i >= 0; i--) {
                if (v[i] == 2) tmp.push(i);
                else if (v[i] == 1 && !tmp.empty()) {
                    a.emplace_back(tmp.front(), i);
                    tmp.pop();
                }
            }
            while (!tmp.empty()) tmp.pop();
            for (int i = 0; i < 2 * n; i++) {
                if (v[i] == 3) tmp.push(i);
                else if (v[i] == 4 && !tmp.empty()) {
                    b.emplace_back(i, tmp.front());
                    tmp.pop();
                }
            }

            int left3_mx = min(size(b), need - cnt[2] + size(a));
            int left3_mn = max(0, need - cnt[2]);
            if (left3_mn > left3_mx) {
                cout << "0\n";
                continue;
            }

            Seg seg(2 * n);
            for (int i = 0; i < 2 * n; i++) seg.update(1, 0, seg.sz - 1, i, 2 * n - 1, v[i] <= 2 ? 1 : -1);

            b.resize(left3_mx);
            int left2 = need - size(b);
            int right2 = cnt[2] - left2;
            assert(size(a) >= right2);
            a.resize(right2);

            bool ans = false;
            for (auto [i, j] : a) {
                seg.update(1, 0, seg.sz - 1, i, 2 * n - 1, -1);
                seg.update(1, 0, seg.sz - 1, j, 2 * n - 1, -1);
            }
            for (auto [i, j] : b) {
                seg.update(1, 0, seg.sz - 1, i, 2 * n - 1, 1);
                seg.update(1, 0, seg.sz - 1, j, 2 * n - 1, 1);
            }
            if (seg.tree[1] >= 0) ans = true;

            while (!b.empty() && !a.empty() && !ans) {
                auto [i, j] = b.back();
                b.pop_back();
                seg.update(1, 0, seg.sz - 1, i, 2 * n - 1, -1);
                seg.update(1, 0, seg.sz - 1, j, 2 * n - 1, -1);
                tie(i, j) = a.back();
                a.pop_back();
                seg.update(1, 0, seg.sz - 1, i, 2 * n - 1, 1);
                seg.update(1, 0, seg.sz - 1, j, 2 * n - 1, 1);
                if (seg.tree[1] >= 0) ans = true;
            }

            cout << ans << "\n";
        }
    }

    return 0;
}
