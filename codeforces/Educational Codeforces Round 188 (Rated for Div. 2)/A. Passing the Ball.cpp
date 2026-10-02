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

        for (int i = 0; i < n; i++) if (st[i] == 'L') {
            cout << i + 1 << "\n";
            break;
        }
    }

    return 0;
}
