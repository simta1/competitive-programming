#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string st;
    cin >> st;
    int n = st.size();

    int ans = 0;
    auto dfs = [&](auto &&dfs, int cnt, int cur, int sz) -> void {
        if (!cnt) {
            string s = to_string(cur);
            string r = s.substr(0, sz);
            reverse(r.begin(), r.end());
            s += r;
            // cout << s << "::\n";
            ans += s.size() < st.size() || s <= st;
            return;
        }

        for (int d = 0; d <= 9; d++) dfs(dfs, cnt - 1, cur * 10 + d, sz);
    };

    for (int len = 1; len <= n; len++) {
        for (int s = 1; s <= 9; s++) {
            dfs(dfs, len - 1 >> 1, s, len / 2);
        }
    }
    cout << ans;

    return 0;
}
