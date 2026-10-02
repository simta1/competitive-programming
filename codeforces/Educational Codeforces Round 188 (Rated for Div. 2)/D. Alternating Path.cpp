#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        vector<vector<int> > adj(n + 1);
        while (m--) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> visited(n + 1);
        auto bfs = [&](int cur) {
            queue<int> q;
            q.push(cur);
            visited[cur] = 1;

            bool flag = true;
            int cnt[2] = {0};
            while (!q.empty()) {
                auto cur = q.front();
                q.pop();
                ++cnt[visited[cur] - 1];

                for (auto next : adj[cur]) {
                    if (!visited[next]) {
                        visited[next] = 3 - visited[cur];
                        q.push(next);
                    }
                    else {
                        if (visited[next] == visited[cur]) flag = false;
                    }
                }
            }
            return flag ? max(cnt[0], cnt[1]) : 0;
        };


        int ans = 0;
        for (int i = 1; i <= n; i++) if (!visited[i]) ans += bfs(i);
        cout << ans << "\n";
    }

    return 0;
}
