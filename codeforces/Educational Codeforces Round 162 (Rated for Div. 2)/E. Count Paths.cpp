#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
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

        vector<int> cnt(n + 1), has(n + 1);
        vector<int> updated;
        auto f = [&](auto &&f, int cur, int par) -> ll {
            ll res = 0;
            if (!has[v[cur]]) res += cnt[v[cur]];
            ++has[v[cur]];
            for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
                res += f(f, nxt, cur);
            }
            --has[v[cur]];
            return res;
        };

        auto update = [&](auto &&update, int cur, int par, int color) -> void {
            if (!has[v[cur]] && v[cur] != color) {
                ++cnt[v[cur]];
                updated.push_back(v[cur]);
            }
            ++has[v[cur]];
            for (auto nxt : adj[cur]) if (nxt != par && !rm[nxt]) {
                update(update, nxt, cur, color);
            }
            --has[v[cur]];
        };

        auto dnc = [&](auto &&dnc, int cur) -> ll {
            int tot = get_sz(get_sz, cur, -1);
            int ct = get_ct(get_ct, cur, -1, tot);
            // cout << ct << "::\n";
            rm[ct] = 1;

            for (auto x : updated) cnt[x] = 0;
            updated.clear();

            cnt[v[ct]] = 1;
            ll res = 0;
            for (auto nxt : adj[ct]) if (!rm[nxt]) {
                res += f(f, nxt, ct);
                update(update, nxt, ct, v[ct]);
            }
            cnt[v[ct]] = 0;

            for (auto nxt : adj[ct]) if (!rm[nxt]) {
                res += dnc(dnc, nxt);
            }
            return res;
        };
        cout << dnc(dnc, 1) << "\n";
    }

    return 0;
}
