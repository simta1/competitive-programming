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

        sort(v.rbegin(), v.rend());
        int s = 0;
        for (auto e : v) {
            if (s + e > k) break;
            s += e;
        }
        cout << k - s << "\n";
    }

    return 0;
}
