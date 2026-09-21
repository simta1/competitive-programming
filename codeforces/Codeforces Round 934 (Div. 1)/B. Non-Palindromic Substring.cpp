#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename Container>
vector<int> manacher(const Container &orig, typename Container::value_type dummy) { // O(N)
    Container st(orig.size() << 1 | 1, dummy);
    for (int i = 0; i < orig.size(); i++) st[2 * i + 1] = orig[i];
    vector<int> r(st.size());
    for (int i = 1, p = 0; i < st.size(); i++) {
        if (i < p + r[p]) r[i] = min(p + r[p] - i, r[2 * p - i]);
        while (i - r[i] - 1 >= 0 && i + r[i] + 1 < st.size() && st[i - r[i] - 1] == st[i + r[i] + 1]) ++r[i];
        if (p + r[p] < i + r[i]) p = i;
    }
    return r;
} // 중심st[i]인 가장 긴 팰린드롬 길이 : r[2i+1], 중심st[i:i+1] : r[2i+2]

ll f(int a, int b) {
    if (a + b & 1) --b;
    return ll(a + b) * ((b - a) / 2 + 1) / 2;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, q;
        cin >> n >> q;

        string st;
        cin >> st;

        auto r = manacher(st, '*');

        auto ispal = [&](int i, int j) {
            int m = i + j >> 1;
            if (i + j & 1) return r[2 * m + 2] >= j - i + 1;
            return r[2 * m + 1] >= j - i + 1;
        };

        // cout << st << " " << ispal(0, 2) << "--\n";

        vector<int> dp(n, n), dp2(n, n);
        for (int i = n - 1; i >= 0; i--) {
            if (i + 1 < n && st[i] == st[i + 1]) dp[i] = dp[i + 1];
            else dp[i] = i + 1;

            if (i + 2 < n && st[i] == st[i + 2]) dp2[i] = dp2[i + 2];
            else dp2[i] = i + 2;
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            int len = r - l + 1;

            ll ans = !ispal(l, r) ? len : 0;
            if (3 <= len - 1) {
                if (dp2[l] <= r || dp2[l + 1] <= r) {
                    ans += f(3, len - 1);
                }
            }
            if (2 <= len - 1) {
                if (dp[l] <= r) {
                    ans += f(2, len - 1);
                }
            }

            cout << ans << "\n";
        }
    }

    return 0;
}
