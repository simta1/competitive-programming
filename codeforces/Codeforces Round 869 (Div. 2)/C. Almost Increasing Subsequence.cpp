#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> pfs(n);
    for (int i = 1; i < n; i++) pfs[i] = v[i - 1] < v[i];

    vector<int> a;
    for (int i = 1, j = 1; i < n; i = j) {
        while (j < n && pfs[i] == pfs[j]) ++j;
        a.push_back(j - 1);
    }
    // for (auto &e : a) cout << e << " "; cout << "\n";

    for (int i = 1; i < n; i++) pfs[i] += pfs[i - 1];

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << "1\n";
            continue;
        }

        --r;
        int ans = pfs[r] - pfs[l - 1];
        int cnt = lower_bound(a.begin(), a.end(), r) - lower_bound(a.begin(), a.end(), l) + 1;
        // cout << l << " " << r << "::\n";
        // cout << cnt << "::\n";
        bool a = pfs[l] > pfs[l - 1];
        bool b = pfs[r] > pfs[r - 1];
        ans += cnt / 2;
        if (!a && !b) ++ans;
        cout << ans + 1 << "\n";
    }

    return 0;
}
