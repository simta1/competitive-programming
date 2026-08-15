#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string s, t;
    cin >> s >> t;

    bool flag = false;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A' && t[i] == 'B') {
            if (!flag) {
                cout << "-1";
                return 0;
            }
        }
        if (t[i] == 'A') flag = true;
    }

    flag = false;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == 'B' && t[i] == 'A') {
            if (!flag) {
                cout << "-1";
                return 0;
            }
        }
        if (t[i] == 'B') flag = true;
    }

    int cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) if (s[i] != t[i]) {
        if (s[i] == 'B') {
            ++cnt;
        }
        else {
            ++ans;
            if (cnt) --cnt;
        }
    }
    cout << ans + cnt;

    return 0;
}
