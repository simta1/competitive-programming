#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;
        ++n;
        bool isp = true;
        for (int i = 2; i <= n / i; i++) if (n % i == 0) isp = false;
        if (isp) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
