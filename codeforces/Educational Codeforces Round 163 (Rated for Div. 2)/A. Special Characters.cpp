#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        if (n & 1) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 0; i < n / 2; i++) {
                if (i & 1) cout << "AA";
                else cout << "BB";
            }
            cout << "\n";
        }
    }

    return 0;
}
