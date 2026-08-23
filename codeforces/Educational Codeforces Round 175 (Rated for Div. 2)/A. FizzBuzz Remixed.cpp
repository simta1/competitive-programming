#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int a[15] = {0};
    for (int i = 0; i < 15; i++) {
        a[i] = (i % 3 == i % 5);
        if (i) a[i] += a[i - 1];
    }
    int cnt = a[14];

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;
        cout << n / 15 * cnt + a[n % 15] << "\n";
    }

    return 0;
}
