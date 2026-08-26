#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int cnt[2]{};
        for (auto ch : st) ++cnt[ch - 'A'];
        int mn = max(cnt[0] - a, cnt[1] - b);
        // cout << mn << " " << c << " " << d << "::\n";

        // mn <= z+w
        // z<=c
        // w<=d

        if (mn > c + d) {
            cout << "NO\n";
            continue;
        }

        int have = 0;
        int n = st.size();
        vector<int> v[2];
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && ~(st[i] + i + st[j] + j) & 1) ++j;
            int len = j - i;
            if (len == 1) continue;
            // cout << st.substr(i, len) << "::\n";
            if (len & 1) have += len / 2;
            else {
                v[st[i] == 'B'].push_back(len / 2);
            }
        }

        int cursum = 0;
        sort(v[0].begin(), v[0].end());
        sort(v[1].begin(), v[1].end());
        for (auto x : v[0]) {
            int use = min(c, x);
            c -= use;
            cursum += use;
            x -= use;
            if (x) {
                --x;
                use = min(d, x);
                d -= use;
                cursum += use;
                x -= use;
            }
        }
        for (auto x : v[1]) {
            int use = min(d, x);
            d -= use;
            cursum += use;
            x -= use;
            if (x) {
                --x;
                use = min(c, x);
                c -= use;
                cursum += use;
                x -= use;
            }
        }
        cursum += min(c + d, have);
        if (cursum >= mn) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
