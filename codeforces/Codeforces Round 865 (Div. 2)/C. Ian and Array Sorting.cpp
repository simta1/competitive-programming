#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<ll> v(n);
        for (auto &e : v) cin >> e;

        if ([&]() {
            if (n & 1) return true;
            ll sum[2]{};
            for (int i = 0; i < n; i++) sum[i & 1] += v[i];
            return sum[0] <= sum[1];
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
