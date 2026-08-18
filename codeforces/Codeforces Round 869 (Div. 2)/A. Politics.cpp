#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        string st;
        cin >> st;
        int ans = 1;
        for (int i = 1; i < n; i++) {
            string x;
            cin >> x;
            ans += st == x;
        }
        cout << ans << "\n";
    }

    return 0;
}
