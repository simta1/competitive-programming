#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    string st = string(100, 'A') + string(100, 'T') + string(10, 'A') + "TA";

    int t = 0, at = 0, a = 0, ta = 0, ata = 0;
    vector<pair<int, int>> v_at, v_ata;
    for (int i = st.size() - 1; i >= 0; i--) {
        if (st[i] == 'T') {
            ++t;
            ta += a;
        }
        else {
            ++a;
            at += t;
            ata += ta;
            if (at) v_at.emplace_back(at, i);
            if (ata) v_ata.emplace_back(ata, i);
        }
    }

    reverse(v_at.begin(), v_at.end());
    reverse(v_ata.begin(), v_ata.end());

    int q;
    for (cin >> q; q--;) {
        int g, c;
        cin >> g >> c;

        vector<int> ans_g(st.size()), ans_c(st.size());
        for (auto [cnt, idx] : v_ata) {
            while (g >= cnt) {
                ++ans_g[idx];
                g -= cnt;
            }
        }
        for (auto [cnt, idx] : v_at) {
            while (c >= cnt) {
                ++ans_c[idx];
                c -= cnt;
            }
        }

        string ans;
        for (int i = 0; i < st.size(); i++) {
            ans += string(ans_g[i], 'G');
            ans += string(ans_c[i], 'C');
            ans += st[i];
        }
        assert(ans.size() <= 500);
        cout << ans << "\n";
    }

    return 0;
}
