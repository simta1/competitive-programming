#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;

main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n + 1);
        for (int k = 1; k <= n; k++) cin >> v[k];

        vector<int> imos(n);
        for (int k = 1; k <= n; k++) {
            ll l = ll(v[k]) * k;
            ll r = ll(v[k] + 1) * k;
            if (l < n) ++imos[l];
            if (r < n) --imos[r];
        }

        for (int i = 1; i < n; i++) imos[i] += imos[i - 1];

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!imos[i]) ans.push_back(i);
        }

        cout << ans.size() << "\n";
        for (auto e : ans) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
