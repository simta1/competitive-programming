#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    auto a = v;
    sort(a.begin(), a.end());

    int mn = n, mx = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] != v[i]) {
            mn = min(mn, i);
            mx = max(mx, i);
        }
    }

    if (!~mx || mx - mn + 1 <= k) cout << "Yes";
    else cout << "No";

    return 0;
}
