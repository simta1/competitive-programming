#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;

int digitSum(int n) {
    int res = 0;
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    vector dp(900'001, vector<int>(10));
    for (int i = 1; i <= 9; i++) ++dp[i][i];
    for (int i = 10; i <= 900'000; i++) {
        int sum = 0;
        for (int tmp = i; tmp; tmp /= 10) {
            ++dp[i][tmp % 10];
            sum += tmp % 10;
        }
        for (int d = 0; d < 10; d++) dp[i][d] += dp[sum][d];
    }

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        if (st.size() == 1) cout << st << "\n";
        else {
            vi cnt(10);
            for (auto ch : st) ++cnt[ch - '0'];

            for (int i = 1; i <= 900'000; i++) {
                if ([&]() {
                    int sum = 0;
                    for (int d = 0; d < 10; d++) {
                        if (cnt[d] < dp[i][d]) return false;
                        sum += d * (cnt[d] - dp[i][d]);
                    }
                    return sum == i;
                }()) {
                    for (int d = 9; d >= 0; d--) {
                        for (int _ = cnt[d] - dp[i][d]; _--;) cout << d;
                    }
                    while (1) {
                        cout << i;
                        if (i <= 9) break;
                        i = digitSum(i);
                    }
                    cout << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}
