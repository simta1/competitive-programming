#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, s;
    cin >> n >> s;

    if (s == 1) {
        cout << 1;
        return 0;
    }

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    sort(v.begin(), v.end());

    int c1 = 0, c2 = 0, ans = 0, len = 0;
    for (auto e : v) {
        int nlen = len + (e + 2) / 3;
        int n1 = c1 + (e % 3 == 1);
        int n2 = c2 + (e % 3 == 2);
        int x = nlen - min(n1, n2) - max(0, n1 - n2) / 2;
        if (x <= s - 2) {
            len = nlen;
            c1 = n1;
            c2 = n2;
            ++ans;
        }
    }

    ans += min(n - ans, 2);
    cout << ans;

    return 0;
}
