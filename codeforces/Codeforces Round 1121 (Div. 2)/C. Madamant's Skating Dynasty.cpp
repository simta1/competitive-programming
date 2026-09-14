#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    constexpr ll MOD = 998'244'353;

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector<int> v(n);
        for (auto &e : v) cin >> e;

        sort(v.rbegin(), v.rend());

        ll dp_sum = 0, dp_cnt = 1, sum = v[0], cnt = 1;
        for (int i = 1; i < n; i++) {
            dp_sum = dp_sum * cnt + dp_cnt * (sum - cnt * v[i] % MOD);
            dp_cnt *= cnt;
            sum += v[i];
            ++cnt;
            dp_sum %= MOD;
            dp_cnt %= MOD;
            sum %= MOD;
        }
        if (dp_sum < 0) dp_sum += MOD;
        cout << dp_sum << "\n";
    }

    return 0;
}
