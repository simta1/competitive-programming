#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int sum = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            sum ^= x;
        }

        if (sum == 0) cout << "0\n";
        else if (n & 1) cout << sum << "\n";
        else cout << "-1\n";
    }

    return 0;
}
