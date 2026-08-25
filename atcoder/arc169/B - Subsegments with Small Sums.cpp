#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    ll s;
    cin >> n >> s;

    vector<ll> pfs(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> pfs[i];
        pfs[i] += pfs[i - 1];
    }

    vector<ll> dp(n + 2);
    for (int l = n; l >= 1; l--) {
        int m = upper_bound(pfs.begin(), pfs.end(), s + pfs[l - 1]) - pfs.begin() - 1;
        dp[l] = n - l + 1 + dp[m + 1];
    }

    cout << accumulate(dp.begin(), dp.end(), 0LL);

    return 0;
}
