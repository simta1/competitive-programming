#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        cout << "1 ";
        for (int i = n; i >= 2; i--) cout << i << " ";
        for (int i = 1; i <= n; i++) cout << i << " " << i << " ";
        for (int i = 1; i <= n; i++) cout << i << " ";
        cout << "\n";
    }

    return 0;
}
