#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);


    int TC;
    for (cin >> TC; TC--;) {
        // int a, b, c;
        // cin >> a >> b >> c;
        // cout << (a ^ b) + (b ^ c) + (c ^ a) << "\n";
/*
6
30
6
62
30
126
30
2147483646
*/
        int l, r;
        cin >> l >> r;
        int idx = 29;
        // for (int i = 29; i >= 0; i--) cout << (l >> i & 1); cout << "\n";
        // for (int i = 29; i >= 0; i--) cout << (r >> i & 1); cout << "\n";
        // for (int i = 29; i >= 0; i--) {
        //     cout << (!(l >> i & 1) || (r >> i & 1)) << "::\n";
        // }
        while ((l >> idx & 1) || (~r >> idx & 1)) --idx;
        // cout << idx << "\n";
        int mask = (1 << idx + 1) - 1;
        int same = r & ~mask;
        int a = same | 1 << idx;
        int b = same | ((1 << idx) - 1);
        int c = l;
        while (c == a || c == b) ++c;
        // cout << a << " " << b << ":: ";
        // cout << (a ^ b) + (b ^ c) + (c ^ a) << "\n";
        cout << a << " " << b << " " << c << "\n";
    }

    return 0;
}
