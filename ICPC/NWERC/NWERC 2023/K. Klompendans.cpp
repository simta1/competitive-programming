#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;

    vector<pair<int, int>> dpos[2];
    dpos[0] = {
        {a, b}, {a, -b}, {-a, b}, {-a, -b},
        {b, a}, {b, -a}, {-b, a}, {-b, -a}
    };
    dpos[1] = {
        {c, d}, {c, -d}, {-c, d}, {-c, -d},
        {d, c}, {d, -c}, {-d, c}, {-d, -c}
    };

    vector visited(n, vector<array<bool, 2>>(n));
    queue<array<int, 3>> q;
    q.push({0, 0, 0});
    q.push({0, 0, 1});
    visited[0][0][0] = visited[0][0][1] = 1;

    while (!q.empty()) {
        auto [ci, cj, p] = q.front();
        q.pop();
        for (auto [di, dj] : dpos[!p]) {
            int ni = ci + di;
            int nj = cj + dj;
            if (ni >= 0 && nj >= 0 && ni < n && nj < n && !visited[ni][nj][!p]) {
                visited[ni][nj][!p] = 1;
                q.push({ni, nj, !p});
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans += visited[i][j][0] || visited[i][j][1];
        }
    }
    cout << ans;

    return 0;
}
