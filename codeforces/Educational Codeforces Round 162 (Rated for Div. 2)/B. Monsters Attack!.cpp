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

        using pii = pair<int, int>;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            mp[abs(x)] += v[i];
        }

        if ([&]() -> bool {
            int t = 0;
            ll have = 0;
            while (!mp.empty()) {
                auto it = mp.begin();
                auto [x, a] = *it;
                mp.erase(it);

                if (have >= a) {
                    have -= a;
                    continue;
                }

                a -= have;
                have = 0;

                // cout << x << " " << a << "::\n";

                // k * need >= a
                // need > (a - 1) / k
                int need = (a - 1) / k + 1;
                t += need;
                if (t > x) return false;

                have += ll(k) * need;
                have -= a;
            }
            return true;
        }()) cout << "YES\n";
        else cout << "NO\n";


    }

    return 0;
}
