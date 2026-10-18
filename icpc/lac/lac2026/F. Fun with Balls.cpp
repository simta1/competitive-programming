#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, sz;
    int mx;
    DSU(int n) : p(n), sz(n, 1), mx(1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int a) {
        while (a != p[a]) a = p[a] = p[p[a]];
        return a;
    }
    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        p[a] = b;
        sz[b] += sz[a];
        mx = max(mx, sz[b]);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr int N = 17;
    // cout << N * (N + 1) / 2;

    int n;
    cin >> n;

    static int a[N * (N + 1) / 2];
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> v[N];
    int it = 0;
    for (int i = 0; i < N; i++) {
        v[i].resize(i + 1);
        for (int j = 0; j <= i; j++) v[i][j] = a[it++];
    }

    static int mp[N][N];
    int id = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            mp[i][j] = id++;
        }
    }

    vector<array<int, 4>> edges;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            if (j + 1 <= i) edges.push_back({i, j, i, j + 1});
            if (i + 1 < N) edges.push_back({i, j, i + 1, j});
            if (i + 1 < N && j + 1 < N) edges.push_back({i, j, i + 1, j + 1});
        }
    }

    int ans = 0;
    static int color[N][N];
    for (int mask = 0; mask < (1 << N); mask++) {
        int ri = 0, rj = 0;
        for (int i = N - 1; i >= 0; i--) {
            int dj = mask >> i & 1;
            for (int k = 0; k <= i; k++) {
                int ci = ri + k;
                int cj = rj + k * dj;
                color[ci][cj] = v[i][v[i].size() - 1 - k];
            }
            ++ri;
            rj += !dj;
        }

        DSU dsu(N * (N + 1) / 2);
        for (auto [i1, j1, i2, j2] : edges) {
            if (color[i1][j1] == color[i2][j2] && color[i1][j1]) {
                dsu.merge(mp[i1][j1], mp[i2][j2]);
            }
        }
        ans = max(ans, dsu.mx);
    }

    cout << ans;

    return 0;
}
