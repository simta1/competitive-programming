#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (i + j + k + 3 <= x) ans = max(ans, v[i] + v[j] + v[k]);
            }
        }
    }
    cout << ans;

    return 0;
}
