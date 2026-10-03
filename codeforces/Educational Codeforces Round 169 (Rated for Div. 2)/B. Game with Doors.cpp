#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int t;
    for (cin >> t; t--;) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        if (b < c || d < a) cout << "1\n";
        else cout << min(b, d) - max(a, c) + (b != d) + (a != c) << "\n";
    }

    return 0;
}
