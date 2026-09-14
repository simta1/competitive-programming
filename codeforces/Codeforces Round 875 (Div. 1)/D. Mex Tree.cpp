#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void chmin(int &a, int b) {
    a = min(a, b);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int mxcnt = 1;
        while ((mxcnt + 1) * (mxcnt + 2) / 2 <= 3 * n / 2) ++mxcnt;

        constexpr int INF = 1e8;
        auto dfs = [&](auto &&dfs, int cur, int par) -> array<vector<int>, 2> {
            array<vector<int>, 2> dp = {{
                {INF, 1},
                {INF, 2}
            }};

            for (auto nxt : adj[cur]) if (nxt != par) {
                auto dp2 = dfs(dfs, nxt, cur);
                array<vector<int>, 2> ndp;
                ndp[0].resize(min(mxcnt + 1, int(dp[0].size()) + int(dp2[0].size()) - 1), INF);
                ndp[1].resize(min(mxcnt + 1, int(dp[1].size()) + int(dp2[1].size()) - 1), INF);
                for (int c1 = 0; c1 < 2; c1++) {
                    for (int c2 = 0; c2 < 2; c2++) {
                        for (int cnt1 = 1; cnt1 < dp[c1].size(); cnt1++) {
                            for (int cnt2 = 1; cnt2 < dp2[c2].size(); cnt2++) {
                                if (c1 == c2) {
                                    if (cnt1 + cnt2 <= mxcnt) chmin(ndp[c1][cnt1 + cnt2], dp[c1][cnt1] + dp2[c2][cnt2] + cnt1 * cnt2 * (1 + c1));
                                }
                                else {
                                    chmin(ndp[c1][cnt1], dp[c1][cnt1] + dp2[c2][cnt2]);
                                }
                            }
                        }
                    }
                }
                swap(ndp, dp);
            }
            return dp;
        };
        auto dp = dfs(dfs, 1, -1);
        int mn = INF;
        for (int color = 0; color < 2; color++) {
            for (int cnt = 1; cnt < dp[color].size(); cnt++) {
                mn = min(mn, dp[color][cnt]);
            }
        }
        cout << n * ll(n + 1) - mn << "\n";
    }

    return 0;
}
