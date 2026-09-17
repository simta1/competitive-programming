#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll n;
        cin >> n;
        ll cnt = 1;
        while (n > 3) {
            n /= 4;
            cnt *= 2;
        }
        cout << cnt << "\n";
    }

    return 0;
}
