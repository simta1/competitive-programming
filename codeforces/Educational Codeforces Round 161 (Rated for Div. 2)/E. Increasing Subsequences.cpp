#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        ll x;
        cin >> x;

        --x;
        int mx = 1e9;
        int mn = 1;
        vector<int> ans;
        while (x) {
            if (x & 1) {
                ans.push_back(mx--);
                --x;
            }
            else {
                ans.push_back(mx--);
                ans.push_back(mn++);
                x = x - 2 >> 1;
            }
        }
        cout << ans.size() << "\n";
        for (auto &e : ans) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
