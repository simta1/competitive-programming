#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector v(n, vector<int>(n));
    for (auto &r : v) for (auto &e : r) cin >> e;

    vector<int> visited(n, -1);
    bool flag = 1;
    for (int i = 0; i < n; i++) {
        for (auto e : v[i]) {
            if (visited[e / n] == i) flag = 0;
            visited[e / n] = i;
        }
    }

    if (flag) {
        cout << "0";
        return 0;
    }

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < n; i++) {
        for (auto e : v[i]) adj[i].emplace_back(e / n, e);
    }

    vector<bool> used(n * n);
    auto match = [&]() {
        vector<int> ml(n, -1), mr(n, -1), vr(n);
        int t = 1;
        auto dfs = [&](auto &&dfs, int l) -> bool {
            for (auto [r, id] : adj[l]) if (!used[id] && vr[r] != t) {
                vr[r] = t;
                if (!~mr[r] || dfs(dfs, mr[r])) {
                    ml[l] = id;
                    mr[r] = l;
                    return true;
                }
            }
            return false;
        };
        for (int i = 0; i < n; ++i, ++t) dfs(dfs, i);
        return ml;
    };

    for (int j = 0; j < n; j++) {
        auto ml = match();
        for (int i = 0; i < n; i++) {
            v[i][j] = ml[i];
            used[ml[i]] = 1;
        }
    }

    cout << n * (n - 1) / 2 << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i][j] > v[j][i]) swap(v[i][j], v[j][i]);
            cout << v[i][j] << " " << v[j][i] << "\n";
        }
    }

    return 0;
}
