#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int query(int r, int c) {
    cout << "? " << r << " " << c << endl;
    int res;
    cin >> res;
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, m;
        cin >> n >> m;

        int a = query(1, 1);
        int b = query(1, m);
        int i, j;
        if (a > b) {
            j = 1 + a;
            i = 1 + query(1, j);
        }
        else if (a < b) {
            j = m - b;
            i = 1 + query(1, j);
        }
        else {
            if (2 * a == m - 1) {
                j = 1 + a;
                i = 1 + query(1, j);
            }
            else {
                i = 1 + a;
                j = 1 + query(i, 1);
            }
        }

        cout << "! " << i << " " << j << endl;
    }

    return 0;
}
