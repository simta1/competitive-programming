#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, b, a;
    cin >> n >> b >> a;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++) v[i] += v[i - 1];

    auto check = [&](int cnt) {
        ll need;
        if (cnt <= a) need = v[cnt] / 2;
        else need = v[cnt - a] + (v[cnt] - v[cnt - a]) / 2;
        return need <= b;
    };

    int lo = 0, hi = n + 1;
    while (lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo;

    return 0;
}
