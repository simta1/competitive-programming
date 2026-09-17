#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int lg = __lg(2 * n + 1);
        vector<pair<int, string> > v(lg);
        for (auto &[cnt, st] : v) {
            cin >> st;
            cnt = 0;
            for (auto ch : st) cnt += ch == '1';
        }
        sort(v.begin(), v.end(), [&](auto a, auto b) {
            return a.first > b.first;
        });

        cout << [&]() {
            vector<bool> used(n + 1);
            for (int j = 0; j < n; j++) {
                int cur = 0;
                for (int i = 0; i < lg; i++) if (v[i].second[j] - '0') cur |= 1 << i;
                if (cur < 1 || cur > n) return 0LL;
                if (used[cur]) return 0LL;
                used[cur] = 1;
            }

            ll ans = 1;
            for (int i = 0, j = 1; i < lg; i = j) {
                while (j < lg && v[j].first == v[i].first) ++j;
                for (int k = 2; k <= j - i; k++) ans *= k;
            }
            return ans;
        }() << "\n";
    }

    return 0;
}
