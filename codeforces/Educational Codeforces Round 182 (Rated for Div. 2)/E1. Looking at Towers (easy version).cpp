#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;
    auto add = [&](ll &a, ll b) {
        a += b;
        if (a >= MOD) a -= MOD;
    };

    static ll pw[5005] = {1};
    for (int i = 1; i <= 5000; i++) pw[i] = pw[i - 1] * 2 % MOD;

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        auto comp = v;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (auto &e : v) e = lower_bound(comp.begin(), comp.end(), e) - comp.begin() + 1;

        vector<int> l, r;
        for (auto e : v) {
            if (l.empty() || l.back() < e) l.push_back(e);
        }
        for (int i = n - 1; i >= 0; i--) {
            if (r.empty() || r.back() < v[i]) r.push_back(v[i]);
        }

        vector dp(n + 1, vector<ll>(comp.size() + 1));
        dp[0][0] = 1;
        vector<ll> ldp(n);
        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];
            int cur = v[i];
            auto it = lower_bound(l.begin(), l.end(), cur);
            if (it != l.end() && *it == cur) {
                int prv = it == l.begin() ? 0 : *prev(it);
                if (cur == comp.size()) ldp[i] = dp[i][prv];
                for (int j = cur + 1; j <= comp.size(); j++) add(dp[i + 1][j], dp[i][j]);
                add(dp[i + 1][cur], dp[i][prv]);
                add(dp[i + 1][cur], dp[i][cur]);
            }
            else {
                for (int j = cur + 1; j <= comp.size(); j++) add(dp[i + 1][j], dp[i][j]);
            }
        }

        vector dp2(n + 1, vector<ll>(comp.size() + 1));
        dp2[0][0] = 1;
        vector<ll> rdp(n);
        for (int i = 0; i < n; i++) {
            dp2[i + 1] = dp2[i];
            int cur = v[n - 1 - i];
            auto it = lower_bound(r.begin(), r.end(), cur);
            if (it != r.end() && *it == cur) {
                int prv = it == r.begin() ? 0 : *prev(it);
                if (cur == comp.size()) rdp[n - 1 - i] = dp2[i][prv];
                for (int j = cur + 1; j <= comp.size(); j++) add(dp2[i + 1][j], dp2[i][j]);
                add(dp2[i + 1][cur], dp2[i][prv]);
                add(dp2[i + 1][cur], dp2[i][cur]);
            }
            else {
                for (int j = cur + 1; j <= comp.size(); j++) add(dp2[i + 1][j], dp2[i][j]);
            }
        }

        ll ans = 0;
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                if (v[r] == comp.size() && v[l] == comp.size()) {
                    ans += ldp[l] * rdp[r] % MOD * (l + 1 < r ? pw[r - l - 1] : 1) % MOD;
                    ans %= MOD;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
