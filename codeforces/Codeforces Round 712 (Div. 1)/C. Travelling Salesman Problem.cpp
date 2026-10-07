#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    ll ans = 0;
    for (auto &[a, c] : v) {
        cin >> a >> c;
        ans += c;
        c += a;
    }

    sort(v.begin(), v.end());
    int prvE = v[0].second;
    for (auto [s, e] : v) {
        if (prvE < s) ans += s - prvE;
        prvE = max(prvE, e);
    }
    cout << ans;

    return 0;
}
