#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        string st;
        cin >> st;

        cout << [&]() {
            string nst;
            int res = 0;
            for (auto ch : st) {
                if (ch != '4') nst += ch;
                else ++res;
            }
            st = nst;
            nst = "";

            int n = st.size();
            vector<int> cnt(n + 1);
            for (int i = 1; i <= n; i++) {
                cnt[i] = cnt[i - 1] + (st[i - 1] == '2');
            }

            int ans = min(cnt[n], n - cnt[n]);
            for (int i = 2; i <= n; i++) {
                ans = min(ans, (i - 1) - cnt[i - 1] + cnt[n] - cnt[i - 1]);
            }
            return ans + res;
        }() << "\n";
    }

    return 0;
}
