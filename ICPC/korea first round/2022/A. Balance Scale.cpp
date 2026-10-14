#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    int a, b;
    cin >> a >> b;

    for (int i = 3; i <= n; i++) {
        int x;
        cin >> x;
        if (a == b) a += x;
        else if (a < b) a += x;
        else b += x;
    }

    int d = abs(b - a);
    int ans = 0;
    for (auto e : {100, 50, 20, 10, 5, 2, 1}) {
        ans += d / e;
        d %= e;
    }
    cout << ans;

    return 0;
}
