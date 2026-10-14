#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    string swerc = "SWERC";

    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        char ch;
        int x;
        cin >> ch >> x;
        v.emplace_back(swerc.find(ch), x - 1);
    }

    int a[5] = {0, n, 2 * n, 3 * n, 4 * n};
    int mx = 0;
    do {
        vector<int> dp;
        for (auto [x, y] : v) {
            int e = a[x] + y;
            if (dp.empty() || dp.back() < e) dp.push_back(e);
            else *lower_bound(dp.begin(), dp.end(), e) = e;
        }
        mx = max<int>(mx, dp.size());
    } while (next_permutation(a, a + 4));

    cout << n - mx;

    return 0;
}
