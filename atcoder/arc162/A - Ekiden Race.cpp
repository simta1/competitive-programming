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

        vector<int> indeg(n + 1);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (v[i] > v[j]) {
                    ++indeg[v[i]];
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) if (!indeg[i]) ++ans;
        cout << ans << "\n";
    }

    return 0;
}
