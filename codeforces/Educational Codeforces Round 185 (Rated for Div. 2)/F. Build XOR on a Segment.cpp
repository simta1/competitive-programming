#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void chmax(int &a, int b) { a = max(a, b); }

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    int q;
    cin >> q;

    vector<vector<array<int, 3>>> qs(n);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        --l, --r;
        qs[r].push_back({l, x, i});
    }

    array<array<int, 4096>, 13> dp;
    for (auto &r : dp) r.fill(-1);
    for (int i = 0; i < n; i++) {
        auto ndp = dp;
        ndp[1][v[i]] = i;
        for (int cnt = 1; cnt < 12; cnt++) {
            for (int mask = 0; mask < 4096; mask++) {
                chmax(ndp[cnt + 1][mask ^ v[i]], dp[cnt][mask]);
            }
        }
        swap(ndp, dp);

        for (auto [l, x, qIdx] : qs[i]) {
            for (int cnt = 1; cnt <= 12; cnt++) {
                if (dp[cnt][x] >= l) {
                    ans[qIdx] = cnt;
                    break;
                }
            }
        }
    }

    for (auto e : ans) cout << e << " ";

    return 0;
}
