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
            if (e) ++cnt;
        }

        if (cnt & 1) {
            cout << "-1\n";
            continue;
        }

        vector<pair<int, int>> ans;
        for (int i = 0, j = 0; i < n; i = j) {
            if (!v[i]) {
                ans.emplace_back(i, i);
                j = i + 1;
            }
            else {
                j = i + 1;
                while (!v[j]) ++j;
                if (v[i] == v[j]) {
                    if (j == i + 1) {
                        ans.emplace_back(i, j);
                    }
                    else {
                        ans.emplace_back(i, j - 2);
                        ans.emplace_back(j - 1, j);
                    }
                }
                else {
                    ans.emplace_back(i, j - 1);
                    ans.emplace_back(j, j);
                }

                ++j;
            }

        }

        cout << ans.size() << "\n";
        for (auto [a, b] : ans) cout << a + 1 << " " << b + 1 << "\n";
    }

    return 0;
}
