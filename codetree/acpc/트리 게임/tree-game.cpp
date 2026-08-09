#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Trie {
    struct Node {
        int mp[2] = {-1, -1};
    };
    int mx = 0;
    vector<Node> tree = {Node()};
    int mxqry(int x) {
        int cur = 0;
        int res = 0;
        for (int i = 16; i >= 0; i--) {
            bool bit = x >> i & 1;
            if (~tree[cur].mp[!bit]) {
                cur = tree[cur].mp[!bit];
                res |= 1 << i;
            }
            else cur = tree[cur].mp[bit];
        }
        return res;
    }
    void insert(int x) {
        int cur = 0;
        for (int i = 16; i >= 0; i--) {
            bool bit = x >> i & 1;
            if (!~tree[cur].mp[bit]) {
                tree[cur].mp[bit] = tree.size();
                tree.emplace_back();
            }
            cur = tree[cur].mp[bit];
        }
        mx = max(mx, mxqry(x));
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> sz(n + 1, 1), dp(n + 1), in(n + 1), out(n + 1), euler(n + 1);
    int dfsi = 0;
    auto mkt = [&](auto &&mkt, int cur, int par) -> void {
        in[cur] = ++dfsi;
        euler[dfsi] = cur;
        for (auto [nxt, w] : adj[cur]) if (nxt != par) {
            dp[nxt] = dp[cur] ^ w;
            mkt(mkt, nxt, cur);
            sz[cur] += sz[nxt];
        }
        out[cur] = dfsi;
    };
    mkt(mkt, 1, -1);

    Trie trie;
    vector<int> ans(n + 1);
    auto dfs = [&](auto &&dfs, int cur, int par, bool keep) -> void {
        int heavy = 0;
        for (auto [nxt, w] : adj[cur]) if (nxt != par) {
            if (!heavy || sz[heavy] < sz[nxt]) heavy = nxt;
        }

        for (auto [nxt, w] : adj[cur]) if (nxt != par && nxt != heavy) dfs(dfs, nxt, cur, false);

        if (heavy) dfs(dfs, heavy, cur, true);
        trie.insert(dp[cur]);
        for (auto [nxt, w] : adj[cur]) if (nxt != par && nxt != heavy) {
            for (int i = in[nxt]; i <= out[nxt]; i++) trie.insert(dp[euler[i]]);
        }
        ans[cur] = trie.mx;

        if (!keep) trie = Trie();
    };
    dfs(dfs, 1, -1, true);

    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";

    return 0;
}