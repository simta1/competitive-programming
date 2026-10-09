#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> dp(n + 1);
    while (m--) {
        int x;
        cin >> x;
        for (int i = 1; i <= x; i++) ++dp[i];
        sort(dp.begin() + 1, dp.begin() + x + 1);
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
