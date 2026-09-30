#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string st;
    cin >> st;

    ll ans = 0;
    for (int i = 0, j = 0; i < st.size(); i = j) {
        while (j < st.size() && st[i] == st[j]) ++j;
        if (st[i] == '>') {
            ll cnt = j - i;
            ans += cnt * (cnt + 1) / 2;
        }
    }
    cout << ans;

    return 0;
}
