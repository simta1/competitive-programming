#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    vector<pair<int, int>> a(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto [x1, y1] = v[i];
            auto [x2, y2] = v[j];
            a[i * n + j] = {x1 + x2, y1 + y2};
        }
    }

    int ans = 0;
    sort(a.begin(), a.end());
    for (int i = 0, j = 0; i < a.size(); i = j) {
        while (j < a.size() && a[i] == a[j]) ++j;
        ans = max(ans, j - i);
    }
    cout << ans;

    return 0;
}
