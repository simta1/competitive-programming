#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, x, k;
    cin >> n >> x >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    ll ans = 0;
    multiset<int> s;
    for (int i = n; i >= 1 - k; i--) {
        if (i >= 1) s.insert(v[i] / 2);
        if (i <= n - k) {
            if ((i + k) % (x + 1) == 0) {
                auto it = prev(s.end());
                ans += *it;
                s.erase(it);
            }
            else s.erase(s.begin());
        }
    }

    cout << ans;

    return 0;
}
