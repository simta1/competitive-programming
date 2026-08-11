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

        for (int i = n - 1; i >= 1; i--) v[i] -= v[i - 1];
        for (int i = 1, j = 2; i < n; i = j) {
            while (j < n && ~(v[i] + v[j]) & 1) ++j;
            sort(v.begin() + i, v.begin() + j);
        }
        for (int i = 1; i < n; i++) v[i] += v[i - 1];
        for (auto &e : v) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
