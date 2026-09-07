#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string a, b, c;
        cin >> a >> b >> c;

        if ([&]() {
            for (int i = 0; i < n; i++) {
                if (c[i] != a[i] && c[i] != b[i]) return true;
            }
            return false;
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
