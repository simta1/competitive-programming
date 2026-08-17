#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int l, r, n;
        cin >> l >> r >> n;

        int len1 = __lg(l) + 1;
        int len2 = __lg(r) + 1;
        string ans;
        if (len1 == len2) {
            bool flag = false;
            for (int i = len1 - 1; i >= 0; i--) {
                bool a = l >> i & 1;
                bool b = r >> i & 1;
                if (a != b) flag = true;
                if (flag) ans += '0';
                else ans += char('0' + a);
            }
        }
        else if (len1 + 1 == len2) {
            ans = string(len2 * (len2 - 1), '0');
            for (int i = 0; i < len2 - 1; i++) if (l >> (len1 - 1 - i) & 1) ans[len2 * i] = '1';
        }
        else {
            ans = string(len2 * (len2 - 1), '0');
            ans[0] = '1';
        }
        for (int i = 0; i < n; i++) cout << ans[i % ans.size()];
        cout << "\n";
    }

    return 0;
}
