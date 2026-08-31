#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string st;
        cin >> st;

        bool ans = true;
        char a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (!isdigit(st[i])) {
                if (i + 1 == n || !isdigit(st[i + 1])) ;
                else ans = false;

                if (a <= st[i]) a = st[i];
                else ans = false;
            }
            else {
                if (b <= st[i]) b = st[i];
                else ans = false;
            }
        }
        if (ans) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
