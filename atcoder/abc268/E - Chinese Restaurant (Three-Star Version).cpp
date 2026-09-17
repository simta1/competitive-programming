#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;

main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    vector<int> imos(n + 2);

    int idx = 0;
    auto f = [&](int a, int b) {
        // if (idx == 0) cout << "--\n";
        int i2;
        if (a <= b) {
            int len = b - a + 1;
            i2 = idx + len - 1;
            assert(i2 < n);
            // cout << a << " " << b << " " << idx << " " << i2 << "::\n";
            imos[idx] += a;
            imos[idx + 1] += 1 - a;
            imos[i2 + 1] += -b - 1;
            imos[i2 + 2] += b;
        }
        else {
            int len = a - b + 1;
            i2 = idx + len - 1;
            assert(i2 < n);
            // cout << a << " " << b << " " << idx << " " << i2 << "::\n";
            imos[idx] += a;
            imos[idx + 1] += -1 - a;
            imos[i2 + 1] += -b + 1;
            imos[i2 + 2] += b;
        }
        idx = i2 + 1;
    };

    if (n & 1) {
        for (int i = 0; i < n; i++) {
            int d = i - v[i];
            if (d < 0) d += n;

            if (d <= n / 2) {
                // [d:0], [1:n/2], [n/2:d)
                idx = 0;
                f(d, 0);
                f(1, n / 2);
                if (n / 2 >= d + 1) f(n / 2, d + 1);
            }
            else {
                // [n-d:n/2], [n/2:0], [1:n-d)
                idx = 0;
                f(n - d, n / 2);
                f(n / 2, 0);
                if (1 <= n - d - 1) f(1, n - d - 1);
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            int d = i - v[i];
            if (d < 0) d += n;

            if (d <= n / 2) {
                // [d:0], [1:n/2 - 1], [n/2:d)
                idx = 0;
                f(d, 0);
                f(1, n / 2 - 1);
                if (n / 2 >= d + 1) f(n / 2, d + 1);
            }
            else {
                // [n-d:n/2], [n/2 - 1:0], [1:n-d)
                idx = 0;
                f(n - d, n / 2);
                f(n / 2 - 1, 0);
                if (1 <= n - d - 1) f(1, n - d - 1);
            }
        }
    }

    for (int i = 1; i < n; i++) imos[i] += imos[i - 1];
    for (int i = 1; i < n; i++) imos[i] += imos[i - 1];
    cout << *min_element(imos.begin(), imos.begin() + n);

    return 0;
}
