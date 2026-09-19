#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        if (n & 1) {
            cout << "-1\n";
            continue;
        }

        vector<pair<int, int>> ans;
        for (int i = 0; i < n; i += 2) {
            if (v[i] == v[i + 1]) ans.emplace_back(i, i + 1);
            else {
                ans.emplace_back(i, i);
                ans.emplace_back(i + 1, i + 1);
            }
        }

        cout << ans.size() << "\n";
        for (auto [a, b] : ans) cout << a + 1 << " " << b + 1 << "\n";
    }

    return 0;
}
