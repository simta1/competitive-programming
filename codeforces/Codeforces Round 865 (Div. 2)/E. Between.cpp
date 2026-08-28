#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        while (m--) {
            int a, b;
            cin >> a >> b;
            if (a == 1) continue;
            adj[b].push_back(a);
        }

        vector<vector<int>> node(n + 1);
        vector<int> dp(n + 1);
        queue<int> q;
        q.push(1);
        dp[1] = 1;
        node[dp[1]].push_back(1);
        int cnt = 0, sum = 0, mx = 0;
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            ++cnt;
            sum += dp[cur];
            mx = max(mx, dp[cur]);
            for (auto nxt : adj[cur]) if (!dp[nxt]) {
                dp[nxt] = dp[cur] + 1;
                node[dp[nxt]].push_back(nxt);
                q.push(nxt);
            }
        }

        if (cnt < n) cout << "INFINITE\n";
        else {
            cout << "FINITE\n";
            vector<vector<int>> ans(mx);
            for (int i = mx; i >= 1; i--) {
                for (auto x : node[i]) {
                    for (int j = 0; j < i; j++) ans[j].push_back(x);
                }
            }

            cout << sum << "\n";
            for (auto &r : ans) for (auto e : r) cout << e << " ";
            cout << "\n";
        }
    }

    return 0;
}
