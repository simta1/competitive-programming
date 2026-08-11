#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> c(n + 1);
        vector<vector<int>> cnodes(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            cnodes[c[i]].push_back(i);
        }
        vector<int> k(n + 1);
        for (int i = 1; i <= n; i++) cin >> k[i];
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> dep(n + 1), euler(2 * n - 1), pos(n + 1);
        int sz = 0;
        auto mkt = [&](auto &&mkt, int cur, int par) -> void {
            euler[pos[cur] = sz++] = cur;
            for (auto nxt : adj[cur]) if (nxt != par) {
                dep[nxt] = dep[cur] + 1;
                mkt(mkt, nxt, cur);
                euler[sz++] = cur;
            }
        };
        mkt(mkt, 1, -1);
        int lg = __lg(sz);
        vector<vector<int>> ac(lg + 1, euler);
        for (int i = 1; i <= lg; i++) {
            for (int j = 0; j + (1 << i) - 1 < sz; j++) {
                int u = ac[i - 1][j];
                int v = ac[i - 1][j + (1 << i - 1)];
                ac[i][j] = dep[u] < dep[v] ? u : v;
            }
        }
        auto getLCA = [&](int a, int b) {
            auto [l, r] = minmax(pos[a], pos[b]);
            int i = __lg(r - l + 1);
            int u = ac[i][l];
            int v = ac[i][r - (1 << i) + 1];
            return dep[u] < dep[v] ? u : v;
        };

        vector<vector<int>> chd(n + 1);
        vector<int> sub(n + 1);
        for (int color = 1; color <= n; color++) {
            if (cnodes[color].empty()) {
                cout << "-1 ";
                continue;
            }
            int tot = cnodes[color].size();
            auto &nodes = cnodes[color];
            sort(nodes.begin(), nodes.end(), [&](int a, int b) {
                return pos[a] < pos[b];
            });
            int tmp = nodes.size();
            for (int i = 1; i < tmp; i++) nodes.push_back(getLCA(nodes[i - 1], nodes[i]));
            sort(nodes.begin(), nodes.end(), [&](int a, int b) {
                return pos[a] < pos[b];
            });
            nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
            int root = nodes[0];
            for (int i = 1; i < nodes.size(); i++) {
                int u = getLCA(nodes[i - 1], nodes[i]);
                int v = nodes[i];
                chd[u].push_back(v);
            }

            priority_queue<pair<int, int>> pq;
            ll ans = 0;
            auto dfs = [&](auto &&dfs, int cur) -> void {
                sub[cur] = (c[cur] == color);
                for (auto nxt : chd[cur]) {
                    dfs(dfs, nxt);
                    int w = min<int>(sub[nxt], tot - sub[nxt]);
                    int cnt = dep[nxt] - dep[cur];
                    ans += w * ll(cnt);
                    pq.emplace(w, cnt);
                    sub[cur] += sub[nxt];
                }
            };
            dfs(dfs, root);

            int cur = k[color] - 1;
            while (!pq.empty()) {
                auto [w, cnt] = pq.top();
                pq.pop();
                int use = min(cur, cnt);
                ans -= use * ll(w);
                cur -= use;
                if (!cur) break;
            }
            cout << ans << " ";

            for (auto x : nodes) {
                chd[x].clear();
                sub[x] = 0;
            }
        }
        cout << "\n";
    }

    return 0;
}
