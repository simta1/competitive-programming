#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        vector ans(2, vector<int>(n));
        int cur = 1;
        for (int j = 1; j < n; j += 2) {
            ans[0][j] = cur++;
            ans[1][j - 1] = cur++;
        }
        for (int j = 2; j < n; j += 2) {
            ans[0][j] = cur++;
            ans[1][j - 1] = cur++;
        }
        ans[0][0] = cur++;
        ans[1][n - 1] = cur++;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) cout << ans[i][j] << " ";
            cout << "\n";
        }
    }

    return 0;
}
