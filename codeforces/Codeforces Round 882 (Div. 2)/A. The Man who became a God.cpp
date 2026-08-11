#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        vector<int> d;
        for (int i = 1; i < n; i++) d.push_back(abs(v[i] - v[i - 1]));
        sort(d.rbegin(), d.rend());
        int ans = 0;
        for (int i = k - 1; i < d.size(); i++) ans += d[i];
        cout << ans << "\n";
    }

    return 0;
}
