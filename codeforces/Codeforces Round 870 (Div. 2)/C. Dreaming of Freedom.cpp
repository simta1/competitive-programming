#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        if ([&]() -> bool {
            for (int i = 1; i <= n / i; i++) if (n % i == 0) {
                if (i >= 2 && i <= m) return false;
                if (n / i >= 2 && n / i <= m) return false;
            }
            return true;
        }()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
