#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &e : v) cin >> e;

    constexpr ll MOD = 998'244'353;

    vector dp(n, vector<ll>(n + 1));
    vector dp2(n, vector<ll>(n + 1));
    ll sum = 0;

    vector<int> left(n + 1, 0);
    if (!~v[0]) {
        for (int val = 1; val <= n; val++) dp[0][val] = dp2[0][val] = 1;
        sum = n;
    }
    else {
        int val = v[0];
        sum = dp[0][val] = dp2[0][val] = 1;
        for (int i = 1; i <= n; i++) if (i != val) left[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        vector<int> vals;
        if (~v[i]) {
            vals = {v[i]};
        }
        else {
            vals.resize(n);
            iota(vals.begin(), vals.end(), 1);
        }

        for (auto val : vals) {
            dp[i][val] = sum - dp2[i - 1][val];
            if (dp[i][val] < 0) dp[i][val] += MOD;

            dp2[i][val] = dp2[i - 1][val] + dp[i][val];
            if (dp2[i][val] >= MOD) dp2[i][val] -= MOD;
            if (i >= val && left[val] <= i - val) {
                dp2[i][val] -= dp[i - val][val];
                if (dp2[i][val] < 0) dp2[i][val] += MOD;
            }
        }

        if (~v[i]) {
            for (int j = 1; j <= n; j++) if (j != v[i]) left[j] = i + 1;
        }

        sum = 0;
        for (int val = 1; val <= n; val++) sum += dp2[i][val];
        sum %= MOD;
    }

    cout << accumulate(dp2[n - 1].begin(), dp2[n - 1].end(), 0LL) % MOD;

    return 0;
}
