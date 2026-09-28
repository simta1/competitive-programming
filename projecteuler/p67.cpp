#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    static int a[100][100];
    constexpr int n = 100;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            a[i][j] += max(j ? a[i - 1][j - 1] : 0, a[i - 1][j]);
        }
    }
    cout << *max_element(a[99], a[99] + 100);

    return 0;
}
