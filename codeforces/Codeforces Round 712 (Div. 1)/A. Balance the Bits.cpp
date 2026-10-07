#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        string st;
        cin >> st;

        int cnt[2]{};
        for (auto ch : st) ++cnt[ch - '0'];
        int o = cnt[1];

        string a(n, '('), b(n, '(');
        if ([&]() {
            if (o & 1) return false;
            o >>= 1;

            int asum = 0, bsum = 0;
            for (int i = 0; i < n; i++) {
                if (st[i] == '1') {
                    if (o > 0) {
                        a[i] = b[i] = '(';
                        ++asum, ++bsum;
                        --o;
                    }
                    else {
                        a[i] = b[i] = ')';
                        --asum, --bsum;
                    }
                }
                else {
                    if (asum > bsum) {
                        a[i] = ')', b[i] = '(';
                        --asum, ++bsum;
                    }
                    else {
                        a[i] = '(', b[i] = ')';
                        ++asum, --bsum;
                    }
                }
                // cout << i << " " << asum << " " << bsum << "::\n";
                if (asum < 0 || bsum < 0) return false;
            }
            return asum == 0 && bsum == 0;
        }()) cout << "YES\n" << a << "\n" << b << "\n";
        else cout << "NO\n";
    }

    return 0;
}
