#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<set<int>> s(n + 1);
    vector<int> dp(n + 1);
    auto dfs = [&](auto &&dfs, int cur, int par) -> void {
        if (cur != 1 && adj[cur].size() == 1) {
            s[cur] = {v[cur]};
            dp[cur] = 0;
            return;
        }

        int sum = 0;
        int child = 0;
        int h = -1;
        for (auto nxt : adj[cur]) if (nxt != par) {
            ++child;
            v[nxt] ^= v[cur];
            dfs(dfs, nxt, cur);
            if (!~h || s[h].size() < s[nxt].size()) h = nxt;
            sum += dp[nxt];
        }

        set<int> tmp;
        bool flag = false;
        for (auto nxt : adj[cur]) if (nxt != par && nxt != h) {
            for (auto e : s[nxt]) {
                flag |= s[h].count(e) || tmp.count(e);
                tmp.insert(e);
            }
        }

        if (flag) {
            map<int, int> mp;
            int mx = 0;
            for (auto nxt : adj[cur]) if (nxt != par) {
                for (auto e : s[nxt]) mx = max(mx, ++mp[e]);
            }
            dp[cur] = sum + child - mx;
            for (auto [e, cnt] : mp) if (cnt == mx) s[cur].insert(e);
        }
        else {
            dp[cur] = sum + child - 1;
            swap(s[cur], s[h]);
            for (auto nxt : adj[cur]) if (nxt != par && nxt != h) {
                s[cur].merge(s[nxt]);
            }
        }
    };
    dfs(dfs, 1, -1);

    cout << dp[1] + (s[1].find(0) == s[1].end());


    return 0;
}
