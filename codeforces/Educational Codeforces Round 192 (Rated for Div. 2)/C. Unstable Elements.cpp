#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        vector<int> cnt(n + 1);
        for (int i = 0, j = 1; i < n; i = j) {
            while (j < n && v[i] == v[j]) ++j;
            ++cnt[j - i];
        }

        vector<int> sum(n + 1);
        for (int i = 1; i <= n; i++) sum[i] = cnt[i] * i;

        // for (auto &e : cnt) cout << e << " "; cout << "\n";
        // for (auto &e : sum) cout << e << " "; cout << "\n";

        // auto sufmn = cnt;
        // for (int i = n - 1; i >= 1; i--) {
        //     if (!sufmn[i]) sufmn[i] = sufmn[i + 1];
        //     else if (sufmn[i + 1]) sufmn[i] = min(sufmn[i], sufmn[i + 1]);
        // }

        for (int i = n - 1; i >= 1; i--) {
            sum[i] += sum[i + 1];
            cnt[i] += cnt[i + 1];
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            // cout << i << " " << sum[i] << " " << cnt[i] << "\n";
            if (cnt[i] - (i + 1 <= n ? cnt[i + 1] : 0) > 0) {
                // cout << i << " " << sum[i] << " " << cnt[i] << " " << sufmn[i] << "\n";
                // cout << (sum[i] - (i - 1) * cnt[i]) << " " << k << "::\n";
                ans += cnt[i] && abs(sum[i] - k) % cnt[i] == 0 && (sum[i] - (i - 1) * cnt[i] <= k);
            }
        }
        cout << ans << "\n";
        
    }

    return 0;
}
