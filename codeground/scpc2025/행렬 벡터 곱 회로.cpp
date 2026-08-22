#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++) {
        int n;
        cin >> n;

        vector<string> v(n);
        for (auto &st : v) cin >> st;

        vector<pair<int, int>> qs;
        vector<array<int, 256>> pos((n + 7) / 8);
        int top = n;
        for (int i = 0; i < (n + 7) / 8; i++) {
            int sz = i < n / 8 ? 8 : n % 8;
            for (int j = 0; j < sz; j++) pos[i][1 << j] = i * 8 + j + 1;
            for (int mask = 1; mask < (1 << sz); mask++) if (mask & (mask - 1)) {
                int a = mask & (mask - 1);
                int b = mask & -mask;
                qs.emplace_back(pos[i][a], pos[i][b]);
                pos[i][mask] = ++top;
            }
        }

        vector<int> ans;
        for (auto &st : v) {
            vector<int> tmp;
            for (int i = 0; i < (n + 7) / 8; i++) {
                int sz = i < n / 8 ? 8 : n % 8;
                int mask = 0;
                for (int j = 0; j < sz; j++) {
                    int idx = i * 8 + j;
                    if (st[idx] == '1') mask |= 1 << j;
                }
                if (mask) tmp.push_back(pos[i][mask]);
            }
            int cur = tmp[0];
            for (int i = 1; i < tmp.size(); i++) {
                qs.emplace_back(cur, tmp[i]);
                cur = ++top;
            }
            ans.push_back(cur);
        }
        cout << "Case #" << tc << "\n";
        cout << qs.size() << "\n";
        for (auto [a, b] : qs) cout << a << " " << b << "\n";
        for (auto e : ans) cout << e << " ";
        cout << "\n";
    }

    return 0;
}
