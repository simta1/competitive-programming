#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    int m = accumulate(v.begin(), v.end(), 0);
    int q = m / n, r = m % n;

    ll ans = 0;
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < r; i++) {
        ans += abs(q + 1 - v[i]);
    }
    for (int i = r; i < n; i++) {
        ans += abs(q - v[i]);
    }
    assert(~ans & 1);
    cout << ans / 2;

    return 0;
}
