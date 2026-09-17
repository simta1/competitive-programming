#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        string st;
        cin >> st;

        int mn = 1e8;
        string ans;
        for (int a = 0; a <= k; a++) {
            int b = k - a;
            string rm(n, '0');
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (st[i] == '(' && cnt < a) {
                    ++cnt;
                    rm[i] = '1';
                }
            }
            cnt = 0;
            for (int i = n - 1; i >= 0; i--) {
                if (st[i] == ')' && cnt < b) {
                    ++cnt;
                    rm[i] = '1';
                }
            }
            int sum = 0, cur = 0;
            for (int i = 0; i < n; i++) if (rm[i] == '0') {
                if (st[i] == '(') ++sum;
                else {
                    if (sum) {
                        --sum;
                        ++cur;
                    }
                }
                // if (a == 0) cout << sum << " " << cnt << ":\n";
            }
            // cout << rm << ": " << cur << "\n";
            if (mn > cur) {
                mn = cur;
                ans = rm;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
