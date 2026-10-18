#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<int, int>> v(n);
    for (auto &[x, y] : v) {
        int a, b;
        cin >> a >> b;
        x = a - b;
        y = a + b;
    }

    sort(v.begin(), v.end(), [&](auto a, auto b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    vector<int> dp;
    for (auto [_, y] : v) {
        if (dp.empty() || dp.back() < y) dp.push_back(y);
        else *lower_bound(dp.begin(), dp.end(), y) = y;
    }
    cout << dp.size();

    return 0;
}
