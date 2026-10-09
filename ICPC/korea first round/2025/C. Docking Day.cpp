#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool inRange(int a, int b, int c) {
    return a < c && c < b || b < c && c < a;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int len = 5;
    vector<int> xs;

    int x[6];
    for (int i = 0; i < 6; i++) {
        cin >> x[i];
        for (int j = -len; j <= len; j++) xs.push_back(x[i] + j);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    for (int i = 0; i < 6; i++) x[i] = lower_bound(xs.begin(), xs.end(), x[i]) - xs.begin();

    int n = xs.size();
    queue<array<int, 3>> q;
    vector dist(n, vector(n, vector<int>(n, -1)));
    q.push({x[0], x[1], x[2]});
    dist[x[0]][x[1]][x[2]] = 0;
    while (!q.empty()) {
        auto [ca, cb, cc] = q.front();
        q.pop();

        vector<array<int, 3>> adj;
        for (int nxt = 0; nxt < n; nxt++) if (nxt != ca && nxt != cb && nxt != cc) {
            if (inRange(ca, nxt, cb) + inRange(ca, nxt, cc) == 1) adj.push_back({nxt, cb, cc});
            if (inRange(cb, nxt, ca) + inRange(cb, nxt, cc) == 1) adj.push_back({ca, nxt, cc});
            if (inRange(cc, nxt, ca) + inRange(cc, nxt, cb) == 1) adj.push_back({ca, cb, nxt});
        }

        for (auto [na, nb, nc] : adj) if (!~dist[na][nb][nc]) {
            dist[na][nb][nc] = dist[ca][cb][cc] + 1;
            q.push({na, nb, nc});
        }
    }

    cout << dist[x[3]][x[4]][x[5]];

    return 0;
}
