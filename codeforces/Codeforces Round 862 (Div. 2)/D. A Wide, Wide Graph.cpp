#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs = [&](int s) {
        vector<int> dist(n + 1, -1);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (auto nxt : adj[cur]) if (!~dist[nxt]) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
        return dist;
    };

    auto d1 = bfs(1);
    int a = max_element(d1.begin(), d1.end()) - d1.begin();
    auto da = bfs(a);
    int b = max_element(da.begin(), da.end()) - da.begin();
    auto db = bfs(b);
    int D = da[b];

    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        ++cnt[max(da[i], db[i])];
    }

    vector<int> ans(n + 1, n);
    int cur = n + 1;
    for (int i = D; i >= 1; i--) {
        cur -= cnt[i];
        ans[i] = cur;
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";

    return 0;
}
