#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, d;
        cin >> n >> d;
        cout << "1 ";
        if (d % 3 == 0 || n >= 3) cout << "3 ";
        if (d % 5 == 0) cout << "5 ";
        if (d % 7 == 0 || n >= 3) cout << "7 ";
        if (d % 9 == 0 || d % 3 == 0 && n >= 3 || n >= 6) cout << "9 ";
        cout << "\n";
    }

    return 0;
}
