#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int n;
    cin >> n;

    constexpr array<int, 9> coins = {500, 200, 100, 50, 20, 10, 5, 2, 1};

    for (int mask = 0; mask < 512; mask++) {
        int tmp = n;
        bool odd = 0;
        for (int i = 0; i < 9; i++) if (mask >> i & 1) {
            int c = coins[i];
            int cnt = tmp / c;
            tmp %= c;
            if (cnt & 1) odd = 1;
        }
        if (!tmp && odd) {
            tmp = n;
            vector<int> ans;
            for (int i = 0; i < 9; i++) if (mask >> i & 1) {
                for (int cnt = tmp / coins[i]; cnt--;) ans.push_back(coins[i]);
                tmp %= coins[i];
            }
            cout << ans.size() << "\n";
            for (auto e : ans) cout << e << " ";
            cout << "\n";
            return 0;
        }
    }

    cout << "splittable";
    return 0;
}
