#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int a[250]{}, b[250]{}, x[250]{}, y[250]{};
    for (int i = 0; i < 250; i++) {
        a[i] = i + 1;
        b[i] = 1000 - i;
    }

    for (int i = 0; i < 7 * 21; i += 7) {
        x[i] = x[i + 1] = x[i + 2] = a[i + 2];
        y[i] = y[i + 1] = y[i + 2] = b[i];

        x[i + 3] = a[i + 3];
        y[i + 3] = b[i + 2];

        x[i + 4] = a[i + 6];
        y[i + 4] = b[i + 3];

        x[i + 5] = x[i + 6] = a[i + 6];
        y[i + 5] = y[i + 6] = b[i + 4];
    }

    for (int i = 147; i < 250; i++) x[i] = a[i], y[i] = b[i];

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) cout << a[i] << " " << b[i] << "\n";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << x[i] << " " << y[i] << "\n";


    return 0;
}
