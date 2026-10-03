#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int t;
    for (cin >> t; t--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        if (n == 2 && v[1] - v[0] > 1) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
