#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    constexpr int MOD = 1e9 + 7;

    vector<int> sz(n + 1);
    vector<bool> rm(n + 1);
    auto get_sz = [&](auto &&get_sz, int cur, int par) -> int {
        sz[cur] = 1;
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            sz[cur] += get_sz(get_sz, nxt, cur);
        }
        return sz[cur];
    };
    auto get_ct = [&](auto &&get_ct, int cur, int par, int tot) -> int {
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            if (sz[nxt] * 2 > tot) return get_ct(get_ct, nxt, cur, tot);
        }
        return cur;
    };

    ll ans = 0;
    vector<int> dep(n + 1), cnt(n + 1), dirt;
    auto dfs = [&](auto &&dfs, int cur, int par) -> void {
        if (dep[cur] <= k) ans += cnt[k - dep[cur]];
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            dep[nxt] = dep[cur] + 1;
            dfs(dfs, nxt, cur);
        }
    };
    auto upd = [&](auto &&upd, int cur, int par) -> void {
        dirt.push_back(cur);
        ++cnt[dep[cur]];
        for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
            upd(upd, nxt, cur);
        }
    };
    auto dnc = [&](auto &&dnc, int cur) -> void {
        int tot = get_sz(get_sz, cur, -1);
        int ct = get_ct(get_ct, cur, -1, tot);
        rm[ct] = 1;
        dep[ct] = 0;
        ++cnt[0];
        dirt.push_back(ct);
        for (auto nxt : adj[ct]) if (!rm[nxt]) {
            dep[nxt] = 1;
            dfs(dfs, nxt, -1);
            upd(upd, nxt, -1);
        }
        for (auto x : dirt) --cnt[dep[x]];
        dirt.clear();
        for (auto nxt : adj[ct]) if (!rm[nxt]) dnc(dnc, nxt);
    };
    dnc(dnc, 1);

    constexpr ll inv2 = MOD + 1 >> 1;
    cout << ans % MOD * k % MOD * (k + 1) % MOD * inv2 % MOD;

    return 0;
}
