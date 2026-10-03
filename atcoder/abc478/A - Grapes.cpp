#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int q = m / n;
    int r = m % n;
    for (int i = 0; i < r; i++) {
        cout << q + 1 << "\n";
    }
    for (int i = r; i < n; i++) {
        cout << q << "\n";
    }

    return 0;
}
