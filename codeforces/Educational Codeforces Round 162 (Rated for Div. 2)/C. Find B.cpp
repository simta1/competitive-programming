#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, q;
        cin >> n >> q;

        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];

        vector<int> one(n + 1);
        vector<ll> pfs(n + 1);
        for (int i = 1; i <= n; i++) {
            pfs[i] = v[i] + pfs[i - 1];
            one[i] = one[i - 1] + (v[i] == 1);
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            if (l == r) {
                cout << "NO\n";
                continue;
            }
            ll sum = pfs[r] - pfs[l - 1];
            int cnt = one[r] - one[l - 1];
            if (sum >= r - l + 1 + cnt) cout << "YES\n";
            else cout << "NO\n";
        }

        
    }

    return 0;
}
