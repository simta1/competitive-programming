#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int a[20][20]{};
    constexpr int n = 20;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string st;
            cin >> st;
            a[i][j] = stoi(st);
        }
    }

    vector<pair<int, int>> dpos;
    for (int k = 0; k < 9; k++) if (k != 4) {
        int a = k / 3 - 1;
        int b = k % 3 - 1;
        dpos.emplace_back(a, b);
    }

    auto inRange = [&](int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < n;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (auto [di, dj] : dpos) {
                int ei = i + 3 * di;
                int ej = j + 3 * dj;
                if (inRange(ei, ej)) {
                    int mul = 1;
                    for (int k = 0; k < 4; k++) {
                        int ci = i + k * di;
                        int cj = j + k * dj;
                        mul *= a[ci][cj];
                    }
                    ans = max(ans, mul);
                }
            }
        }
    }

    cout << ans;

    return 0;
}
