#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m, k;
        cin >> n >> m >> k;
        if (k + (n + m - 1) / m < n) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
