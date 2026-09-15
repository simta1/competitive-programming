#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int as = 0, bs = 0;
    vector<pair<int, int>> v(n);
    for (auto &[a, b] : v) {
        cin >> a >> b;
        as += a;
        bs += b;
    }

    for (int i = 0; i < n; i++) {
        if (bs - as <= v[i].second - v[i].first) {
            cout << i + 1;
            return 0;
        }
    }

    cout << "impossible";
    return 0;
}
