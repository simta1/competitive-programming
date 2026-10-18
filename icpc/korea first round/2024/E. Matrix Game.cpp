#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector a(n, vector<int>(n));
    vector b(n, vector<int>(n));
    for (auto &r : a) for (auto &e : r) cin >> e;
    for (auto &r : b) for (auto &e : r) cin >> e;

    vector<int> v(n);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) v[j] = max(v[j], abs(a[i][j] - b[i][j]));
    }

    int ans = 0;
    while (m--) {
        int j;
        cin >> j;
        ans += v[j - 1];
    }
    cout << ans;

    return 0;
}
