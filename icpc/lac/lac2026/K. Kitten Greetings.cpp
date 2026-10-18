#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    map<int, int> mpx, mpy;
    for (int i = 0; i < n; i++) {
        auto &[x, y] = v[i];
        cin >> x >> y;
        mpx[x] = mpy[y] = i;
    }

    vector mp(n, vector<array<int, 2>>(n));
    int N = 2 * n * (n - 1);
    vector<int> len(N), cat(N);
    int id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            auto [x1, y1] = v[i];
            auto [x2, y2] = v[j];
            len[id] = len[id + 1] = abs(x2 - x1) + abs(y2 - y1);
            cat[id] = cat[id + 1] = j;
            mp[i][j][0] = id++;
            mp[i][j][1] = id++;
        }
    }
    assert(id == N);

    vector<int> adj(N, -1);
    auto addEdge = [&](int u, int v) {
        adj[u] = v;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            auto [x1, y1] = v[i];
            auto [x2, y2] = v[j];
            int y = 2 * y2 - y1;
            if (mpy.count(y)) {
                int k = mpy[y];
                auto [x3, y3] = v[k];
                addEdge(mp[i][j][0], mp[j][k][1]);
            }
            int x = 2 * x2 - x1;
            if (mpx.count(x)) {
                int k = mpx[x];
                auto [x3, y3] = v[k];
                addEdge(mp[i][j][1], mp[j][k][0]);
            }
        }
    }

    ll ans = 0;
    int t = 1;
    vector<int> used(n);
    vector<int> state(N + 1), path;
    auto dfs = [&](auto &&dfs, int cur) -> void {
        state[cur] = 1;
        path.push_back(cur);
        int nxt = adj[cur];
        if (~nxt) {
            if (!state[nxt]) dfs(dfs, nxt);
            else if (state[nxt] == 1) {
                ll sum = 0;
                ++t;
                for (int i = path.size() - 1; i >= 0; i--) {
                    if (used[cat[path[i]]] == t) sum = -1e18;
                    used[cat[path[i]]] = t;
                    sum += len[path[i]];
                    if (path[i] == nxt) break;
                }
                ans = max(ans, sum);
            }
        }
        path.pop_back();
        state[cur] = 2;
    };
    for (int i = 0; i < N; i++) if (!state[i]) dfs(dfs, i);
    cout << ans;

    return 0;
}
