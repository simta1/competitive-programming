#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(const string &st) {
    return 1 << string("RGBY").find(st[0]) | 1 << string("RGBY").find(st[1]);
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, q;
        cin >> n >> q;

        set<int> s[16];
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            string st;
            cin >> st;
            int mask = f(st);
            s[mask].insert(i);
            v[i] = mask;
        }

        while (q--) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            if (x > y) swap(x, y);
            if (v[x] & v[y]) cout << y - x << "\n";
            else {
                constexpr int INF = 1e8;
                int ans = INF;
                for (int mask = 0; mask < 16; mask++) {
                    if (mask & v[x] && mask & v[y] && !s[mask].empty()) {
                        auto it = s[mask].lower_bound(x);
                        if (it != s[mask].end()) {
                            int m = *it;
                            ans = min(ans, m - x + abs(y - m));
                        }
                        if (it != s[mask].begin()) {
                            int m = *prev(it);
                            ans = min(ans, abs(x - m) + abs(y - m));
                        }
                    }
                }
                if (ans == INF) cout << "-1\n";
                else cout << ans << "\n";
            }
        }
    }

    return 0;
}
