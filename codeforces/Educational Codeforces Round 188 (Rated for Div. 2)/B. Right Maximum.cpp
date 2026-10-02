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

        int ans = 0;
        int mx = 0;
        for (auto e : v) {
            if (mx <= e) {
                ++ans;
                mx = e;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
