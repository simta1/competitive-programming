#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n, k;
        cin >> n >> k;

        vector<vector<int>> chd(n + 1);
        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            chd[p].push_back(i);
        }
        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];

        vector<int> in(n + 1), out(n + 1), euler(n + 1);
        int dfsi = 0;
        auto mkt = [&](auto &&mkt, int cur) -> void {
            in[cur] = ++dfsi;
            euler[in[cur]] = cur;
            for (auto nxt : chd[cur]) mkt(mkt, nxt);
            out[cur] = dfsi;
        };
        mkt(mkt, 1);

        bool ans = false;
        for (int i = 1; i <= n; i++) {
            vector<int> cnt(n + 1);
            int need = k;
            int empty = 0;
            bool flag = false;
            for (int j = in[i]; j <= out[i]; j++) {
                int cur = v[euler[j]];
                if (!~cur) ++empty;
                else if (cur == k) {
                    flag = true;
                    break;
                }
                else if (cur < k) {
                    if (++cnt[cur] == 1) --need;
                }
            }
            if (flag) continue;
            if (need == 0 && empty <= 1 || need == 1 && empty == 1) ans = true;
        }
        if (ans) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
