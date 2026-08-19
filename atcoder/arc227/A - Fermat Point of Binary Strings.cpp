#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a[3];
    for (int i = 0; i < 3; i++) {
        string st;
        cin >> st;

        for (int j = 0; j < 2 * n; j++) {
            if (st[j] == '1') a[i].push_back(j);
        }
    }

    ll x = 0;
    string ans(2 * n, '0');
    for (int i = 0; i < n; i++) {
        int mn = min({a[0][i], a[1][i], a[2][i]});
        int mx = max({a[0][i], a[1][i], a[2][i]});
        int idx = mn ^ mx ^ a[0][i] ^ a[1][i] ^ a[2][i];
        x += mx - mn;
        ans[idx] = '1';
    }
    cout << x << "\n" << ans;

    return 0;
}
