#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);

    int TC;
    for (cin >> TC; TC--;) {
        int n;
        cin >> n;

        int cnt = 0;
        vector<int> v(n);
        for (auto &e : v) {
            cin >> e;
            cnt += e;
        }

        vector<int> ans;
        auto f = [&](int idx) {
            ans.push_back(idx);
            v[idx] = v[idx + 1] = v[idx + 2] = (v[idx] ^ v[idx + 1] ^ v[idx + 2]);
        };

        if ([&]() -> bool {
            if (cnt & 1) return false;
            if (cnt == n) return false;

            for (int i = 0, j = 0; i < n;) {
                if (!v[i]) {
                    ++i, ++j;
                    continue;
                }

                while (j < n && v[j]) ++j;

                if (j - i & 1) {
                    while (!v[j] && !v[j + 1]) {
                        f(j - 1);
                        j += 2;
                    }

                    if (!v[j]) { // 01
                        for (int idx = j - 1; idx >= i; idx -= 2) f(idx);
                        i = j;
                        continue;
                    }
                    else { // 1
                        continue;
                    }
                }
                else {
                    if (i) {
                        for (int idx = i - 1; idx <= j - 3; idx += 2) f(idx);
                        i = j;
                        continue;
                    }
                    else if (j < n) {
                        for (int idx = j - 2; idx >= i; idx -= 2) f(idx);
                        i = j;
                        continue;
                    }
                    else return false;
                }
            }
            return true;
        }()) {
            cout << "YES\n";
            cout << ans.size() << "\n";
            for (auto e : ans) cout << e + 1 << " ";
            cout << "\n";
        }
        else cout << "NO\n";
    }

    return 0;
}
