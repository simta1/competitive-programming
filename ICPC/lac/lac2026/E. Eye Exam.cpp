#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int mn = -1e8, mx = 1e8;
    for (int i = 0; i < n; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;

        if (c == 'A') {
            mx = min(mx, a + b - 1 >> 1);
        }
        else if (c == 'B') {
            mn = max(mn, (a + b) / 2 + 1);
        }
        else {
            if (a + b & 1) {
                mx = -1e8, mn = 1e8;
            }
            else {
                int x = a + b >> 1;
                mx = min(mx, x);
                mn = max(mn, x);
            }
        }
    }

    if (mn > mx) cout << "*";
    else cout << mn << " " << mx;

    return 0;
}
