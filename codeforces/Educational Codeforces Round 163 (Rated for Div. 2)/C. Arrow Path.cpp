#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr array<pair<int, int>, 4> dpos = {{
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
}};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string v[2];
        cin >> v[0] >> v[1];
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        vector visited(2, vector<bool>(n));
        visited[0][0] = 1;

        auto inRange = [&](int i, int j) {
            return i >= 0 && j >= 0 && i < 2 && j < n;
        };

        while (!q.empty()) {
            auto [ci, cj] = q.front();
            q.pop();
            for (auto [di, dj] : dpos) {
                int ni = ci + di;
                int nj = cj + dj;
                if (!inRange(ni, nj)) continue;
                if (v[ni][nj] == '>') ++nj;
                else --nj;
                if (!visited[ni][nj]) {
                    visited[ni][nj] = 1;
                    q.emplace(ni, nj);
                }
            }
        }

        if (visited[1][n - 1]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
