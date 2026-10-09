#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int qs[5];
    for (int i = 0; i < 5; i++) cin >> qs[i];

    constexpr array<pair<int, int>, 4> dpos = {{ // lrud
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}
    }};

    int id = 0;
    static vector<array<int, 3>> adj[1001][1001];
    vector<int> cnt(n), tot(n);
    int cx, cy;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (i == 0) cx = x1, cy = y2;
        tot[i] = x2 - x1 + y2 - y1 << 1;
        for (int x = x1; x < x2; x++) {
            adj[x][y2].push_back({1, i, id++});
            adj[x + 1][y1].push_back({0, i, id++});
        }
        for (int y = y1; y < y2; y++) {
            adj[x1][y].push_back({2, i, id++});
            adj[x2][y + 1].push_back({3, i, id++});
        }
    }

    static pair<int, int> ans[100'005];
    ans[0] = {cx, cy};
    int dir = 1, t = 0;
    vector<bool> visited(id);
    while (t < 100'000) {
        if (adj[cx][cy].size() == 2) {
            if (dir == adj[cx][cy][1][0]) swap(adj[cx][cy][0], adj[cx][cy][1]);
            auto [dir1, rect1, id1] = adj[cx][cy][0];
            auto [dir2, rect2, id2] = adj[cx][cy][1];
            if (!cnt[rect2] || cnt[rect1] == tot[rect1]) swap(adj[cx][cy][0], adj[cx][cy][1]);
        }
        auto [ndir, rect, edge] = adj[cx][cy][0];

        if (visited[edge]) break;
        visited[edge] = 1;
        ++cnt[rect];

        if (dir != ndir) {
            ans[t + 1] = ans[t + 2] = ans[t];
            t += 2;
            dir = ndir;
        }
        auto [dx, dy] = dpos[ndir];
        cx += dx, cy += dy;
        ans[++t] = {cx, cy};
    }

    while (t < 100'000) ans[++t] = {cx, cy};

    for (int i = 0; i < 5; i++) {
        auto [x, y] = ans[qs[i]];
        cout << x << " " << y << "\n";
    }

    return 0;
}
