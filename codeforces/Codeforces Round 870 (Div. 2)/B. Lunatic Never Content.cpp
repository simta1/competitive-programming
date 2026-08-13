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

        int g = 0;
        for (int i = 0; i < n; i++) {
            int x = abs(v[i] - v[n - 1 - i]);
            g = __gcd(g, x);
        }
        cout << g << "\n";
    }

    return 0;
}
