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

        int s = 0;
        while (s < n && !v[s]) ++s;

        auto f = [&](int idx) {
            for (int i = idx - 1; i > s; i--) if (!v[i]) return i;
            return -1;
        };

        int ans = 0;
        for (int i = n - 1; i > s; i--) if (v[i]) {
            int idx = f(i);
            if (!~idx) break;
            swap(v[i], v[idx]);
            ++ans;
        }
        cout << ans << "\n";

    }

    return 0;
}
