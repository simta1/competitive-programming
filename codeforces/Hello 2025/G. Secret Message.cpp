#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(int i, int j) {
    int x = 2 * i + j;
    x %= 5;
    return x < 0 ? x + 5 : x;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr array<pair<int, int>, 5> dpos = {{
        {0, 1}, {0, -1}, {-1, 0}, {1, 0}
    }};

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        auto inRange = [&](int i, int j) {
            return i >= 0 && i < n && j >= 0 && j < m;
        };

        vector<string> v(n);
        for (auto &st : v) cin >> st;

        vector<pair<int, int>> a[5];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (v[i][j] == '.') continue;
                a[f(i, j)].emplace_back(i, j);

                for (auto [di, dj] : dpos) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (!inRange(ni, nj) || v[ni][nj] == '.') a[f(ni, nj)].emplace_back(i, j);
                }
            }
        }

        int idx = 0;
        for (int i = 1; i < 5; i++) if (a[idx].size() > a[i].size()) idx = i;

        for (auto [i, j] : a[idx]) v[i][j] = 'S';
        for (int i = 0; i < n; i++) cout << v[i] << "\n";
    }

    return 0;
}
