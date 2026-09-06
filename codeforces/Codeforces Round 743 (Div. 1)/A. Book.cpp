#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        vector<int> indeg(n + 1);
        for (int i = 1; i <= n; i++) {
            int k;
            cin >> k;
            while (k--) {
                int j;
                cin >> j;
                adj[j].push_back(i);
                ++indeg[i];
            }
        }

        queue<int> q;
        vector<int> dep(n + 1);
        for (int i = 1; i <= n; i++) if (!indeg[i]) {
            q.push(i);
            dep[i] = 1;
        }

        int cnt = 0;
        while (!q.empty()) {
            ++cnt;
            auto cur = q.front();
            q.pop();
            for (auto nxt : adj[cur]) {
                if (cur <= nxt) dep[nxt] = max(dep[nxt], dep[cur]);
                else dep[nxt] = max(dep[nxt], dep[cur] + 1);
                if (--indeg[nxt] == 0) q.push(nxt);
            }
        }

        cout << [&]() -> int {
            if (cnt < n) return -1;
            return *max_element(dep.begin(), dep.end());
        }() << "\n";

    }

    return 0;
}
