#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        map<int, int> mp;
        ++mp[0];
        ll ans = 0;
        int cur = 0;
        for (auto ch : st) {
            cur += (ch == '(' ? 1 : -1);
            while (!mp.empty() && mp.begin()->first * 2 < cur) mp.erase(mp.begin());
            ans += mp[cur];
            ++mp[cur];
        }
        cout << ans << "\n";
    }

    return 0;
}
