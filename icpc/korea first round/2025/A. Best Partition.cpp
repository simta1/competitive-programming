#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    vector<int> dp(n + 1, 1e8);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a_mi = i, b_mi = i;
        for (int j = i - 1; j >= 0; j--) {
            if (a_mi == b_mi) dp[i] = min(dp[i], dp[j] + 1);
            if (a[a_mi] > a[j]) a_mi = j;
            if (b[b_mi] > b[j]) b_mi = j;
        }
    }
    cout << dp[n];

    return 0;
}
