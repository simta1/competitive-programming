#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string st;
    cin >> st;

    array<int, 3> cnt{};
    for (auto ch : st) {
        if (ch == 'r') ++cnt[0];
        else if (ch == 'g') ++cnt[1];
        else ++cnt[2];
    }

    sort(cnt.begin(), cnt.end());
    auto [a, b, c] = cnt;

    using ld = double;
    ld ans = 1.5 * a;

    ld pow = 1;
    for (int _ = a; _--;) pow *= 0.5;


    ld aCi = 1;
    for (int i = 0; i <= a; i++) {
        int b2 = b + i;
        int c2 = c + (a - i);
        ans += aCi * pow * min(b2, c2) * 3;
        aCi = aCi / (i + 1) * (a - i);
    }
    cout << fixed << setprecision(12) << ans;

    return 0;
}
